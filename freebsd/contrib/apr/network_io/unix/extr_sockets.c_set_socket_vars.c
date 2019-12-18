#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int protocol; int /*<<< orphan*/  options; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
typedef  TYPE_1__ apr_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_TCP_NODELAY ; 
 int /*<<< orphan*/  apr_sockaddr_vars_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_socket_vars(apr_socket_t *sock, int family, int type, int protocol)
{
    sock->type = type;
    sock->protocol = protocol;
    apr_sockaddr_vars_set(sock->local_addr, family, 0);
    apr_sockaddr_vars_set(sock->remote_addr, family, 0);
    sock->options = 0;
#if defined(BEOS) && !defined(BEOS_BONE)
    /* BeOS pre-BONE has TCP_NODELAY on by default and it can't be
     * switched off!
     */
    sock->options |= APR_TCP_NODELAY;
#endif
}