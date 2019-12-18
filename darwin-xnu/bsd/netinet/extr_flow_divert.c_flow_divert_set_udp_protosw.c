#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct socket {struct protosw* so_proto; int /*<<< orphan*/  so_flags; } ;
struct protosw {int dummy; } ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ SOCK_DOM (struct socket*) ; 
 int /*<<< orphan*/  SOF_FLOW_DIVERT ; 
 int /*<<< orphan*/  g_flow_divert_in6_udp_protosw ; 
 struct protosw g_flow_divert_in_udp_protosw ; 

__attribute__((used)) static void
flow_divert_set_udp_protosw(struct socket *so)
{
        so->so_flags |= SOF_FLOW_DIVERT;
        if (SOCK_DOM(so) == PF_INET) {
                so->so_proto = &g_flow_divert_in_udp_protosw;
        }
#if INET6
        else {
                so->so_proto = (struct protosw *)&g_flow_divert_in6_udp_protosw;
        }
#endif  /* INET6 */
}