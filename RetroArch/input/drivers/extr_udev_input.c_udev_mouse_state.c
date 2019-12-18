#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pointer_y; int /*<<< orphan*/  pointer_x; } ;
typedef  TYPE_1__ udev_input_t ;
struct TYPE_10__ {int /*<<< orphan*/  whd; int /*<<< orphan*/  whu; int /*<<< orphan*/  wd; int /*<<< orphan*/  wu; int /*<<< orphan*/  b5; int /*<<< orphan*/  b4; int /*<<< orphan*/  m; int /*<<< orphan*/  r; int /*<<< orphan*/  l; } ;
typedef  TYPE_2__ udev_input_mouse_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_4 138 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_5 137 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 136 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 135 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 134 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 133 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 132 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 131 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 130 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 
 TYPE_2__* udev_get_mouse (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  udev_mouse_get_x (TYPE_2__*) ; 
 int /*<<< orphan*/  udev_mouse_get_y (TYPE_2__*) ; 
 scalar_t__ udev_pointer_is_off_window (TYPE_1__*) ; 

__attribute__((used)) static int16_t udev_mouse_state(udev_input_t *udev,
      unsigned port, unsigned id, bool screen)
{
   udev_input_mouse_t *mouse = udev_get_mouse(udev, port);

   if (!mouse)
      return 0;

   if (id != RETRO_DEVICE_ID_MOUSE_X && id != RETRO_DEVICE_ID_MOUSE_Y &&
         udev_pointer_is_off_window(udev))
      return 0;

   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
         return screen ? udev->pointer_x : udev_mouse_get_x(mouse);
      case RETRO_DEVICE_ID_MOUSE_Y:
         return screen ? udev->pointer_y : udev_mouse_get_y(mouse);
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

   return 0;
}