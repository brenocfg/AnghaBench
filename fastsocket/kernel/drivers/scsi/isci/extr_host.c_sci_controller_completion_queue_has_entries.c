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
typedef  size_t u32 ;
struct isci_host {size_t completion_queue_get; int /*<<< orphan*/ * completion_queue; } ;

/* Variables and functions */
 scalar_t__ COMPLETION_QUEUE_CYCLE_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ NORMALIZE_GET_POINTER_CYCLE_BIT (size_t) ; 
 size_t SMU_COMPLETION_QUEUE_GET_POINTER_MASK ; 

__attribute__((used)) static bool sci_controller_completion_queue_has_entries(struct isci_host *ihost)
{
	u32 get_value = ihost->completion_queue_get;
	u32 get_index = get_value & SMU_COMPLETION_QUEUE_GET_POINTER_MASK;

	if (NORMALIZE_GET_POINTER_CYCLE_BIT(get_value) ==
	    COMPLETION_QUEUE_CYCLE_BIT(ihost->completion_queue[get_index]))
		return true;

	return false;
}