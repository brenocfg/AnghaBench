#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  error ;
typedef  int apr_status_t ;
typedef  int apr_socklen_t ;
struct TYPE_11__ {scalar_t__ timeout; int local_port_unknown; int local_interface_unknown; int connected; TYPE_2__* local_addr; TYPE_8__* remote_addr; scalar_t__ remote_addr_unknown; int /*<<< orphan*/  socketdes; } ;
typedef  TYPE_3__ apr_socket_t ;
struct TYPE_9__ {int /*<<< orphan*/  sin; } ;
struct TYPE_12__ {int /*<<< orphan*/  port; int /*<<< orphan*/  family; int /*<<< orphan*/  salen; TYPE_1__ sa; int /*<<< orphan*/  ipaddr_len; int /*<<< orphan*/  ipaddr_ptr; } ;
typedef  TYPE_4__ apr_sockaddr_t ;
struct TYPE_13__ {int /*<<< orphan*/  salen; TYPE_1__ sa; } ;
struct TYPE_10__ {scalar_t__ port; int /*<<< orphan*/  ipaddr_len; int /*<<< orphan*/  ipaddr_ptr; } ;

/* Variables and functions */
 int APR_SUCCESS ; 
 scalar_t__ EALREADY ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EINTR ; 
 scalar_t__ EISCONN ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  apr_sockaddr_vars_set (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int apr_wait_for_io_or_timeout (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  generic_inaddr_any ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

apr_status_t apr_socket_connect(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    int rc;        

    do {
        rc = connect(sock->socketdes,
                     (const struct sockaddr *)&sa->sa.sin,
                     sa->salen);
    } while (rc == -1 && errno == EINTR);

    /* we can see EINPROGRESS the first time connect is called on a non-blocking
     * socket; if called again, we can see EALREADY
     */
    if ((rc == -1) && (errno == EINPROGRESS || errno == EALREADY)
                   && (sock->timeout > 0)) {
        rc = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (rc != APR_SUCCESS) {
            return rc;
        }

#ifdef SO_ERROR
        {
            int error;
            apr_socklen_t len = sizeof(error);
            if ((rc = getsockopt(sock->socketdes, SOL_SOCKET, SO_ERROR, 
                                 (char *)&error, &len)) < 0) {
                return errno;
            }
            if (error) {
                return error;
            }
        }
#endif /* SO_ERROR */
    }


    if (memcmp(sa->ipaddr_ptr, generic_inaddr_any, sa->ipaddr_len)) {
        /* A real remote address was passed in.  If the unspecified
         * address was used, the actual remote addr will have to be
         * determined using getpeername() if required. */
        sock->remote_addr_unknown = 0;

        /* Copy the address structure details in. */
        sock->remote_addr->sa = sa->sa;
        sock->remote_addr->salen = sa->salen;
        /* Adjust ipaddr_ptr et al. */
        apr_sockaddr_vars_set(sock->remote_addr, sa->family, sa->port);
    }

    if (sock->local_addr->port == 0) {
        /* connect() got us an ephemeral port */
        sock->local_port_unknown = 1;
    }
    if (!memcmp(sock->local_addr->ipaddr_ptr,
                generic_inaddr_any,
                sock->local_addr->ipaddr_len)) {
        /* not bound to specific local interface; connect() had to assign
         * one for the socket
         */
        sock->local_interface_unknown = 1;
    }

    if (rc == -1 && errno != EISCONN) {
        return errno;
    }

#ifndef HAVE_POLL
    sock->connected=1;
#endif
    return APR_SUCCESS;
}