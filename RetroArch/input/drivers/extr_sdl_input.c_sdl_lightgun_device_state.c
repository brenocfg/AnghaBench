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
struct TYPE_3__ {int mouse_x; int mouse_y; int mouse_l; int mouse_m; int mouse_r; } ;
typedef  TYPE_1__ sdl_input_t ;
typedef  int int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_LIGHTGUN_CURSOR 134 
#define  RETRO_DEVICE_ID_LIGHTGUN_PAUSE 133 
#define  RETRO_DEVICE_ID_LIGHTGUN_START 132 
#define  RETRO_DEVICE_ID_LIGHTGUN_TRIGGER 131 
#define  RETRO_DEVICE_ID_LIGHTGUN_TURBO 130 
#define  RETRO_DEVICE_ID_LIGHTGUN_X 129 
#define  RETRO_DEVICE_ID_LIGHTGUN_Y 128 

__attribute__((used)) static int16_t sdl_lightgun_device_state(sdl_input_t *sdl, unsigned id)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_LIGHTGUN_X:
         return sdl->mouse_x;
      case RETRO_DEVICE_ID_LIGHTGUN_Y:
         return sdl->mouse_y;
      case RETRO_DEVICE_ID_LIGHTGUN_TRIGGER:
         return sdl->mouse_l;
      case RETRO_DEVICE_ID_LIGHTGUN_CURSOR:
         return sdl->mouse_m;
      case RETRO_DEVICE_ID_LIGHTGUN_TURBO:
         return sdl->mouse_r;
      case RETRO_DEVICE_ID_LIGHTGUN_START:
         return sdl->mouse_m && sdl->mouse_r;
      case RETRO_DEVICE_ID_LIGHTGUN_PAUSE:
         return sdl->mouse_m && sdl->mouse_l;
   }

   return 0;
}