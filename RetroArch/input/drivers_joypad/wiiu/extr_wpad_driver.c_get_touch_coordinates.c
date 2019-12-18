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
struct video_viewport {int dummy; } ;
typedef  int /*<<< orphan*/  VPADTouchData ;
typedef  int /*<<< orphan*/  VPADStatus ;

/* Variables and functions */
 int /*<<< orphan*/  apply_clamping (int /*<<< orphan*/ *,struct video_viewport*,int*) ; 
 int /*<<< orphan*/  get_calibrated_point (int /*<<< orphan*/ *,struct video_viewport*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_touch_coordinates(VPADTouchData *point, VPADStatus *vpad,
      struct video_viewport *viewport, bool *clamped)
{
   get_calibrated_point(point, viewport, vpad);
   apply_clamping(point, viewport, clamped);
}