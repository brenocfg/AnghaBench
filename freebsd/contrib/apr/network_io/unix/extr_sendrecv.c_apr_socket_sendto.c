#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  scalar_t__ apr_status_t ;
typedef  int apr_ssize_t ;
struct TYPE_6__ {scalar_t__ timeout; int /*<<< orphan*/  socketdes; } ;
typedef  TYPE_1__ apr_socket_t ;
struct TYPE_7__ {int /*<<< orphan*/  salen; int /*<<< orphan*/  sa; } ;
typedef  TYPE_2__ apr_sockaddr_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ apr_wait_for_io_or_timeout (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int sendto (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ ) ; 

apr_status_t apr_socket_sendto(apr_socket_t *sock, apr_sockaddr_t *where,
                               apr_int32_t flags, const char *buf,
                               apr_size_t *len)
{
    apr_ssize_t rv;

    do {
        rv = sendto(sock->socketdes, buf, (*len), flags, 
                    (const struct sockaddr*)&where->sa, 
                    where->salen);
    } while (rv == -1 && errno == EINTR);

    while ((rv == -1) && (errno == EAGAIN || errno == EWOULDBLOCK)
                      && (sock->timeout > 0)) {
        apr_status_t arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        } else {
            do {
                rv = sendto(sock->socketdes, buf, (*len), flags,
                            (const struct sockaddr*)&where->sa,
                            where->salen);
            } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        *len = 0;
        return errno;
    }
    *len = rv;
    return APR_SUCCESS;
}