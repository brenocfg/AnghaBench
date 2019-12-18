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
typedef  int /*<<< orphan*/  udev_input_t ;
struct TYPE_3__ {int l; int r; int m; int b4; int b5; int wu; int wd; int whu; int whd; } ;
typedef  TYPE_1__ udev_input_mouse_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_4 136 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_5 135 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 134 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 133 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 132 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 131 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 130 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 129 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 128 
 TYPE_1__* udev_get_mouse (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static bool udev_mouse_button_pressed(
      udev_input_t *udev, unsigned port, unsigned key)
{
   udev_input_mouse_t *mouse = udev_get_mouse(udev, port);

   if (!mouse)
      return false;

   switch ( key )
   {
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return mouse->l;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return mouse->r;
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         return mouse->m;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
         return mouse->b4;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
         return mouse->b5;
      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
         return mouse->wu;
      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
         return mouse->wd;
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
         return mouse->whu;
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
         return mouse->whd;
   }

   return false;
}