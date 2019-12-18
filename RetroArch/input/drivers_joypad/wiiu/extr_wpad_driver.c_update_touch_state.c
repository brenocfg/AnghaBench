#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct video_viewport {scalar_t__ height; scalar_t__ y; scalar_t__ width; scalar_t__ x; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ VPADTouchData ;
struct TYPE_7__ {scalar_t__ validity; int /*<<< orphan*/  touched; } ;
struct TYPE_9__ {TYPE_1__ tpNormal; } ;
typedef  TYPE_3__ VPADStatus ;

/* Variables and functions */
 size_t RETRO_DEVICE_ID_ANALOG_X ; 
 size_t RETRO_DEVICE_ID_ANALOG_Y ; 
 int /*<<< orphan*/  VPAD_BUTTON_TOUCH ; 
 scalar_t__ VPAD_VALID ; 
 size_t WIIU_DEVICE_INDEX_TOUCHPAD ; 
 int /*<<< orphan*/  get_touch_coordinates (TYPE_2__*,TYPE_3__*,struct video_viewport*,int*) ; 
 int /*<<< orphan*/  log_coords (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_touchpad (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_get_viewport_info (struct video_viewport*) ; 

__attribute__((used)) static void update_touch_state(int16_t state[3][2], uint64_t *buttons, VPADStatus *vpad)
{
   VPADTouchData point            = {0};
   struct video_viewport viewport = {0};
   bool touch_clamped             = false;

   if (!vpad->tpNormal.touched || vpad->tpNormal.validity != VPAD_VALID)
   {
      *buttons &= ~VPAD_BUTTON_TOUCH;
      return;
   }

   video_driver_get_viewport_info(&viewport);
   get_touch_coordinates(&point, vpad, &viewport, &touch_clamped);

   state[WIIU_DEVICE_INDEX_TOUCHPAD][RETRO_DEVICE_ID_ANALOG_X] = scale_touchpad(
         viewport.x, viewport.x + viewport.width, -0x7fff, 0x7fff, point.x);
   state[WIIU_DEVICE_INDEX_TOUCHPAD][RETRO_DEVICE_ID_ANALOG_Y] = scale_touchpad(
         viewport.y, viewport.y + viewport.height, -0x7fff, 0x7fff, point.y);

#if 0
   log_coords(state[WIIU_DEVICE_INDEX_TOUCHPAD][RETRO_DEVICE_ID_ANALOG_X],
         state[WIIU_DEVICE_INDEX_TOUCHPAD][RETRO_DEVICE_ID_ANALOG_Y]);
#endif

   if (!touch_clamped)
      *buttons |= VPAD_BUTTON_TOUCH;
   else
      *buttons &= ~VPAD_BUTTON_TOUCH;
}