#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  size_t apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_14__ {scalar_t__ nelts; int flags; TYPE_4__* p; TYPE_2__** wakeup_pipe; } ;
typedef  TYPE_5__ apr_pollset_t ;
struct TYPE_12__ {TYPE_2__* f; TYPE_1__* s; } ;
struct TYPE_15__ {scalar_t__ desc_type; int /*<<< orphan*/  rtnevents; TYPE_3__ desc; } ;
typedef  TYPE_6__ apr_pollfd_t ;
typedef  int /*<<< orphan*/  apr_os_sock_t ;
typedef  scalar_t__ apr_interval_time_t ;
typedef  int apr_int32_t ;
struct TYPE_13__ {TYPE_6__* result_set; TYPE_6__* query_set; scalar_t__ maxfd; int /*<<< orphan*/  set_type; int /*<<< orphan*/  exceptset; int /*<<< orphan*/  writeset; int /*<<< orphan*/  readset; } ;
struct TYPE_11__ {int /*<<< orphan*/  filedes; } ;
struct TYPE_10__ {int /*<<< orphan*/  socketdes; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EBADF ; 
 int /*<<< orphan*/  APR_EINTR ; 
 int /*<<< orphan*/  APR_POLLERR ; 
 int /*<<< orphan*/  APR_POLLIN ; 
 int /*<<< orphan*/  APR_POLLOUT ; 
 int APR_POLLSET_WAKEABLE ; 
 scalar_t__ APR_POLL_SOCKET ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  APR_TIMEUP ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HAS_PIPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_get_netos_error () ; 
 int /*<<< orphan*/  apr_pollset_drain_wakeup_pipe (TYPE_5__*) ; 
 int /*<<< orphan*/  apr_sleep (scalar_t__) ; 
 scalar_t__ apr_time_sec (scalar_t__) ; 
 scalar_t__ apr_time_usec (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pipe_select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static apr_status_t impl_pollset_poll(apr_pollset_t *pollset,
                                      apr_interval_time_t timeout,
                                      apr_int32_t *num,
                                      const apr_pollfd_t **descriptors)
{
    int rs;
    apr_uint32_t i, j;
    struct timeval tv, *tvptr;
    fd_set readset, writeset, exceptset;
    apr_status_t rv = APR_SUCCESS;

#ifdef WIN32
    /* On Win32, select() must be presented with at least one socket to
     * poll on, or select() will return WSAEINVAL.  So, we'll just
     * short-circuit and bail now.
     */
    if (pollset->nelts == 0) {
        (*num) = 0;
        if (timeout > 0) {
            apr_sleep(timeout);
            return APR_TIMEUP;
        }
        return APR_SUCCESS;
    }
#endif

    if (timeout < 0) {
        tvptr = NULL;
    }
    else {
        tv.tv_sec = (long) apr_time_sec(timeout);
        tv.tv_usec = (long) apr_time_usec(timeout);
        tvptr = &tv;
    }

    memcpy(&readset, &(pollset->p->readset), sizeof(fd_set));
    memcpy(&writeset, &(pollset->p->writeset), sizeof(fd_set));
    memcpy(&exceptset, &(pollset->p->exceptset), sizeof(fd_set));

#ifdef NETWARE
    if (HAS_PIPES(pollset->p->set_type)) {
        rs = pipe_select(pollset->p->maxfd + 1, &readset, &writeset, &exceptset,
                         tvptr);
    }
    else
#endif
        rs = select(pollset->p->maxfd + 1, &readset, &writeset, &exceptset,
                    tvptr);

    (*num) = rs;
    if (rs < 0) {
        return apr_get_netos_error();
    }
    if (rs == 0) {
        return APR_TIMEUP;
    }
    j = 0;
    for (i = 0; i < pollset->nelts; i++) {
        apr_os_sock_t fd;
        if (pollset->p->query_set[i].desc_type == APR_POLL_SOCKET) {
            fd = pollset->p->query_set[i].desc.s->socketdes;
        }
        else {
            if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
                pollset->p->query_set[i].desc.f == pollset->wakeup_pipe[0]) {
                apr_pollset_drain_wakeup_pipe(pollset);
                rv = APR_EINTR;
                continue;
            }
            else {
#if !APR_FILES_AS_SOCKETS
                return APR_EBADF;
#else
                fd = pollset->p->query_set[i].desc.f->filedes;
#endif
            }
        }
        if (FD_ISSET(fd, &readset) || FD_ISSET(fd, &writeset) ||
            FD_ISSET(fd, &exceptset)) {
            pollset->p->result_set[j] = pollset->p->query_set[i];
            pollset->p->result_set[j].rtnevents = 0;
            if (FD_ISSET(fd, &readset)) {
                pollset->p->result_set[j].rtnevents |= APR_POLLIN;
            }
            if (FD_ISSET(fd, &writeset)) {
                pollset->p->result_set[j].rtnevents |= APR_POLLOUT;
            }
            if (FD_ISSET(fd, &exceptset)) {
                pollset->p->result_set[j].rtnevents |= APR_POLLERR;
            }
            j++;
        }
    }
    if (((*num) = j) != 0)
        rv = APR_SUCCESS;

    if (descriptors)
        *descriptors = pollset->p->result_set;
    return rv;
}