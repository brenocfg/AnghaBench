#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct socket {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  filter_control_unit; } ;
struct TYPE_4__ {TYPE_1__ results; } ;
struct inpcb {TYPE_2__ inp_policyresult; } ;

/* Variables and functions */
 struct inpcb* sotoinpcb (struct socket*) ; 

u_int32_t
necp_socket_get_content_filter_control_unit(struct socket *so)
{
	struct inpcb *inp = sotoinpcb(so);

	if (inp == NULL) {
		return (0);
	}
	return (inp->inp_policyresult.results.filter_control_unit);
}