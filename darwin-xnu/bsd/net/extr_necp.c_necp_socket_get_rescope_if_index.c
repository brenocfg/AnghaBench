#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int /*<<< orphan*/  scoped_interface_index; } ;
struct TYPE_5__ {scalar_t__ result; TYPE_1__ result_parameter; } ;
struct TYPE_6__ {TYPE_2__ results; } ;
struct inpcb {TYPE_3__ inp_policyresult; } ;

/* Variables and functions */
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SCOPED_DIRECT ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SOCKET_SCOPED ; 
 int /*<<< orphan*/  necp_get_primary_direct_interface_index () ; 

u_int
necp_socket_get_rescope_if_index(struct inpcb *inp)
{
	if (inp == NULL) {
		return (0);
	}

	if (inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_SOCKET_SCOPED) {
		return (inp->inp_policyresult.results.result_parameter.scoped_interface_index);
	} else if (inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_SCOPED_DIRECT) {
		return (necp_get_primary_direct_interface_index());
	}

	return (0);
}