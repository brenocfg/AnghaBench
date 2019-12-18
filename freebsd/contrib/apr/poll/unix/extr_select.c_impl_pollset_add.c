#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_13__ {size_t nelts; size_t nalloc; int flags; TYPE_4__* p; TYPE_2__** wakeup_pipe; } ;
typedef  TYPE_5__ apr_pollset_t ;
struct TYPE_11__ {TYPE_2__* f; TYPE_1__* s; } ;
struct TYPE_14__ {scalar_t__ desc_type; int reqevents; TYPE_3__ desc; } ;
typedef  TYPE_6__ apr_pollfd_t ;
typedef  scalar_t__ apr_os_sock_t ;
struct TYPE_12__ {int maxfd; int /*<<< orphan*/  exceptset; int /*<<< orphan*/  writeset; int /*<<< orphan*/  readset; scalar_t__ set_type; TYPE_6__* query_set; } ;
struct TYPE_10__ {scalar_t__ filedes; scalar_t__ is_pipe; } ;
struct TYPE_9__ {scalar_t__ socketdes; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EBADF ; 
 int /*<<< orphan*/  APR_ENOMEM ; 
 int APR_POLLERR ; 
 int APR_POLLHUP ; 
 int APR_POLLIN ; 
 int APR_POLLNVAL ; 
 int APR_POLLOUT ; 
 int APR_POLLPRI ; 
 int APR_POLLSET_WAKEABLE ; 
 scalar_t__ APR_POLL_FILE ; 
 scalar_t__ APR_POLL_SOCKET ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_SETSIZE ; 
 scalar_t__ HAS_PIPES (scalar_t__) ; 
 int /*<<< orphan*/  HAS_SOCKETS (scalar_t__) ; 

__attribute__((used)) static apr_status_t impl_pollset_add(apr_pollset_t *pollset,
                                     const apr_pollfd_t *descriptor)
{
    apr_os_sock_t fd;

    if (pollset->nelts == pollset->nalloc) {
        return APR_ENOMEM;
    }

    pollset->p->query_set[pollset->nelts] = *descriptor;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
#ifdef NETWARE
        /* NetWare can't handle mixed descriptor types in select() */
        if (HAS_PIPES(pollset->p->set_type)) {
            return APR_EBADF;
        }
        else {
            pollset->p->set_type = APR_POLL_SOCKET;
        }
#endif
        fd = descriptor->desc.s->socketdes;
    }
    else {
#if !APR_FILES_AS_SOCKETS
        if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
            descriptor->desc.f == pollset->wakeup_pipe[0])
            fd = (apr_os_sock_t)descriptor->desc.f->filedes;
        else
            return APR_EBADF;
#else
#ifdef NETWARE
        /* NetWare can't handle mixed descriptor types in select() */
        if (descriptor->desc.f->is_pipe && !HAS_SOCKETS(pollset->p->set_type)) {
            pollset->p->set_type = APR_POLL_FILE;
            fd = descriptor->desc.f->filedes;
        }
        else {
            return APR_EBADF;
        }
#else
        fd = descriptor->desc.f->filedes;
#endif
#endif
    }
#if !defined(WIN32) && !defined(NETWARE)        /* socket sets handled with array of handles */
    if (fd >= FD_SETSIZE) {
        /* XXX invent new error code so application has a clue */
        return APR_EBADF;
    }
#endif
    if (descriptor->reqevents & APR_POLLIN) {
        FD_SET(fd, &(pollset->p->readset));
    }
    if (descriptor->reqevents & APR_POLLOUT) {
        FD_SET(fd, &(pollset->p->writeset));
    }
    if (descriptor->reqevents &
        (APR_POLLPRI | APR_POLLERR | APR_POLLHUP | APR_POLLNVAL)) {
        FD_SET(fd, &(pollset->p->exceptset));
    }
    if ((int) fd > pollset->p->maxfd) {
        pollset->p->maxfd = (int) fd;
    }
    pollset->nelts++;
    return APR_SUCCESS;
}