#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ current_state_id; } ;
struct sci_remote_node_context {TYPE_1__ sm; } ;

/* Variables and functions */
 scalar_t__ SCI_RNC_TX_RX_SUSPENDED ; 

bool sci_remote_node_context_is_suspended(struct sci_remote_node_context *sci_rnc)
{
	u32 current_state = sci_rnc->sm.current_state_id;

	if (current_state == SCI_RNC_TX_RX_SUSPENDED)
		return true;
	return false;
}