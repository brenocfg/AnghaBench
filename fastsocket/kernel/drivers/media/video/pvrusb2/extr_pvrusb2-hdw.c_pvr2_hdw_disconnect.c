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
struct pvr2_hdw {int /*<<< orphan*/  big_lock; int /*<<< orphan*/  ctl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 int /*<<< orphan*/  pvr2_hdw_remove_usb_stuff (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_hdw*) ; 

void pvr2_hdw_disconnect(struct pvr2_hdw *hdw)
{
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_disconnect(hdw=%p)",hdw);
	LOCK_TAKE(hdw->big_lock);
	LOCK_TAKE(hdw->ctl_lock);
	pvr2_hdw_remove_usb_stuff(hdw);
	LOCK_GIVE(hdw->ctl_lock);
	LOCK_GIVE(hdw->big_lock);
}