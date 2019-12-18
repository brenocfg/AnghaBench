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
struct TYPE_2__ {scalar_t__ current_state_id; } ;
struct sci_remote_node_context {scalar_t__ destination_state; TYPE_1__ sm; } ;

/* Variables and functions */
 scalar_t__ RNC_DEST_FINAL ; 
 scalar_t__ RNC_DEST_UNSPECIFIED ; 
 scalar_t__ SCI_RNC_INITIAL ; 

__attribute__((used)) static inline bool sci_remote_node_context_is_being_destroyed(
	struct sci_remote_node_context *sci_rnc)
{
	return (sci_rnc->destination_state == RNC_DEST_FINAL)
		|| ((sci_rnc->sm.current_state_id == SCI_RNC_INITIAL)
		    && (sci_rnc->destination_state == RNC_DEST_UNSPECIFIED));
}