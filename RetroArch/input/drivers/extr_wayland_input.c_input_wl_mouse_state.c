#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  middle; int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  delta_y; int /*<<< orphan*/  y; int /*<<< orphan*/  delta_x; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {TYPE_1__ mouse; } ;
typedef  TYPE_2__ input_ctx_wayland_data_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_LEFT 132 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 131 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 130 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 

__attribute__((used)) static int16_t input_wl_mouse_state(input_ctx_wayland_data_t *wl, unsigned id, bool screen)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
         return screen ? wl->mouse.x : wl->mouse.delta_x;
      case RETRO_DEVICE_ID_MOUSE_Y:
         return screen ? wl->mouse.y : wl->mouse.delta_y;
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return wl->mouse.left;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return wl->mouse.right;
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         return wl->mouse.middle;

      /* TODO: Rest of the mouse inputs. */
   }

   return 0;
}