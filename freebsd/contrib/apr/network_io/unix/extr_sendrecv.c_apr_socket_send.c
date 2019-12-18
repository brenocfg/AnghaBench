#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ apr_status_t ;
typedef  int apr_ssize_t ;
struct TYPE_4__ {int options; scalar_t__ timeout; int /*<<< orphan*/  socketdes; } ;
typedef  TYPE_1__ apr_socket_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int APR_INCOMPLETE_WRITE ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ apr_wait_for_io_or_timeout (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int write (int /*<<< orphan*/ ,char const*,int) ; 

apr_status_t apr_socket_send(apr_socket_t *sock, const char *buf, 
                             apr_size_t *len)
{
    apr_ssize_t rv;
    
    if (sock->options & APR_INCOMPLETE_WRITE) {
        sock->options &= ~APR_INCOMPLETE_WRITE;
        goto do_select;
    }

    do {
        rv = write(sock->socketdes, buf, (*len));
    } while (rv == -1 && errno == EINTR);

    while (rv == -1 && (errno == EAGAIN || errno == EWOULDBLOCK) 
                    && (sock->timeout > 0)) {
        apr_status_t arv;
do_select:
        arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        }
        else {
            do {
                rv = write(sock->socketdes, buf, (*len));
            } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        *len = 0;
        return errno;
    }
    if ((sock->timeout > 0) && (rv < *len)) {
        sock->options |= APR_INCOMPLETE_WRITE;
    }
    (*len) = rv;
    return APR_SUCCESS;
}