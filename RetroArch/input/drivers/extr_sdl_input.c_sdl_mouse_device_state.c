#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mouse_b5; int /*<<< orphan*/  mouse_b4; int /*<<< orphan*/  mouse_m; int /*<<< orphan*/  mouse_y; int /*<<< orphan*/  mouse_x; int /*<<< orphan*/  mouse_wd; int /*<<< orphan*/  mouse_wu; int /*<<< orphan*/  mouse_r; int /*<<< orphan*/  mouse_l; } ;
typedef  TYPE_1__ sdl_input_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_4 136 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_5 135 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 134 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 133 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 132 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 131 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 130 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 

__attribute__((used)) static int16_t sdl_mouse_device_state(sdl_input_t *sdl, unsigned id)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return sdl->mouse_l;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return sdl->mouse_r;
      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
         return sdl->mouse_wu;
      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
         return sdl->mouse_wd;
      case RETRO_DEVICE_ID_MOUSE_X:
         return sdl->mouse_x;
      case RETRO_DEVICE_ID_MOUSE_Y:
         return sdl->mouse_y;
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         return sdl->mouse_m;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
         return sdl->mouse_b4;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
         return sdl->mouse_b5;
   }

   return 0;
}