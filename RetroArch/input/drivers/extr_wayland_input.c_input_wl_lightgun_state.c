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
typedef  int int16_t ;
struct TYPE_4__ {int delta_x; int delta_y; int left; int middle; int right; } ;
struct TYPE_5__ {TYPE_1__ mouse; } ;
typedef  TYPE_2__ input_ctx_wayland_data_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_LIGHTGUN_CURSOR 134 
#define  RETRO_DEVICE_ID_LIGHTGUN_PAUSE 133 
#define  RETRO_DEVICE_ID_LIGHTGUN_START 132 
#define  RETRO_DEVICE_ID_LIGHTGUN_TRIGGER 131 
#define  RETRO_DEVICE_ID_LIGHTGUN_TURBO 130 
#define  RETRO_DEVICE_ID_LIGHTGUN_X 129 
#define  RETRO_DEVICE_ID_LIGHTGUN_Y 128 

__attribute__((used)) static int16_t input_wl_lightgun_state(input_ctx_wayland_data_t *wl, unsigned id)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_LIGHTGUN_X:
         return wl->mouse.delta_x;
      case RETRO_DEVICE_ID_LIGHTGUN_Y:
         return wl->mouse.delta_y;
      case RETRO_DEVICE_ID_LIGHTGUN_TRIGGER:
         return wl->mouse.left;
      case RETRO_DEVICE_ID_LIGHTGUN_CURSOR:
         return wl->mouse.middle;
      case RETRO_DEVICE_ID_LIGHTGUN_TURBO:
         return wl->mouse.right;
      case RETRO_DEVICE_ID_LIGHTGUN_START:
         return wl->mouse.middle && wl->mouse.right;
      case RETRO_DEVICE_ID_LIGHTGUN_PAUSE:
         return wl->mouse.middle && wl->mouse.left;
   }

   return 0;
}