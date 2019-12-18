#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_9__ {int local_port_unknown; TYPE_4__* local_addr; int /*<<< orphan*/  socketdes; } ;
typedef  TYPE_3__ apr_socket_t ;
struct TYPE_7__ {scalar_t__ sin_port; } ;
struct TYPE_8__ {TYPE_1__ sin; } ;
struct TYPE_10__ {TYPE_2__ sa; int /*<<< orphan*/  salen; } ;
typedef  TYPE_4__ apr_sockaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int bind (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

apr_status_t apr_socket_bind(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    if (bind(sock->socketdes, 
             (struct sockaddr *)&sa->sa, sa->salen) == -1) {
        return errno;
    }
    else {
        sock->local_addr = sa;
        /* XXX IPv6 - this assumes sin_port and sin6_port at same offset */
        if (sock->local_addr->sa.sin.sin_port == 0) { /* no need for ntohs() when comparing w/ 0 */
            sock->local_port_unknown = 1; /* kernel got us an ephemeral port */
        }
        return APR_SUCCESS;
    }
}