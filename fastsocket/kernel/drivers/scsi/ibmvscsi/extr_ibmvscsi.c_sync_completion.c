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
struct srp_event_struct {int /*<<< orphan*/  comp; int /*<<< orphan*/ * xfer_iu; int /*<<< orphan*/ * sync_srp; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sync_completion(struct srp_event_struct *evt_struct)
{
	/* copy the response back */
	if (evt_struct->sync_srp)
		*evt_struct->sync_srp = *evt_struct->xfer_iu;
	
	complete(&evt_struct->comp);
}