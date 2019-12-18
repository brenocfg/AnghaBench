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
struct wiimote_t {int /*<<< orphan*/  orient; int /*<<< orphan*/  accel_calib; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMOOTH_PITCH ; 
 int /*<<< orphan*/  SMOOTH_ROLL ; 
 scalar_t__ WIIMOTE_IS_FLAG_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIUSE_SMOOTHING ; 
 scalar_t__ WIIUSE_USING_ACC (struct wiimote_t*) ; 
 int /*<<< orphan*/  apply_smoothing (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void idle_cycle(struct wiimote_t* wm)
{
	/*
	 *	Smooth the angles.
	 *
	 *	This is done to make sure that on every cycle the orientation
	 *	angles are smoothed.  Normally when an event occurs the angles
	 *	are updated and smoothed, but if no packet comes in then the
	 *	angles remain the same.  This means the angle wiiuse reports
	 *	is still an old value.  Smoothing needs to be applied in this
	 *	case in order for the angle it reports to converge to the true
	 *	angle of the device.
	 */
	//printf("idle_cycle()\n");///
	if (WIIUSE_USING_ACC(wm) && WIIMOTE_IS_FLAG_SET(wm, WIIUSE_SMOOTHING)) {
		apply_smoothing(&wm->accel_calib, &wm->orient, SMOOTH_ROLL);
		apply_smoothing(&wm->accel_calib, &wm->orient, SMOOTH_PITCH);
	}
}