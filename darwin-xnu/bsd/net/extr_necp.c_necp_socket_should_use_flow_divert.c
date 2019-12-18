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
struct TYPE_3__ {scalar_t__ result; } ;
struct TYPE_4__ {TYPE_1__ results; } ;
struct inpcb {TYPE_2__ inp_policyresult; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SOCKET_DIVERT ; 

bool
necp_socket_should_use_flow_divert(struct inpcb *inp)
{
	if (inp == NULL) {
		return (FALSE);
	}

	return (inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_SOCKET_DIVERT);
}