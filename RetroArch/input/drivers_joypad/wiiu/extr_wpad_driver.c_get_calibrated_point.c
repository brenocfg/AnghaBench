#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct video_viewport {int /*<<< orphan*/  full_height; int /*<<< orphan*/  full_width; } ;
struct TYPE_6__ {void* y; void* x; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ VPADTouchData ;
struct TYPE_7__ {int /*<<< orphan*/  tpNormal; } ;
typedef  TYPE_2__ VPADStatus ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_GAMEPAD ; 
 int /*<<< orphan*/  VPADGetTPCalibratedPoint (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* scale_touchpad (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void get_calibrated_point(VPADTouchData *point, struct video_viewport *viewport, VPADStatus *vpad)
{
   VPADTouchData calibrated720p = {0};

   VPADGetTPCalibratedPoint(PAD_GAMEPAD, &calibrated720p, &(vpad->tpNormal));
   point->x = scale_touchpad(12, 1268, 0, viewport->full_width, calibrated720p.x);
   point->y = scale_touchpad(12, 708, 0, viewport->full_height, calibrated720p.y);
}