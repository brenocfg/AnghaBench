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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  flow_divert_control_unit; } ;
struct TYPE_5__ {scalar_t__ result; TYPE_1__ result_parameter; } ;
struct TYPE_6__ {TYPE_2__ results; } ;
struct inpcb {TYPE_3__ inp_policyresult; } ;

/* Variables and functions */
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SOCKET_DIVERT ; 

u_int32_t
necp_socket_get_flow_divert_control_unit(struct inpcb *inp)
{
	if (inp == NULL) {
		return (0);
	}

	if (inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_SOCKET_DIVERT) {
		return (inp->inp_policyresult.results.result_parameter.flow_divert_control_unit);
	}

	return (0);
}