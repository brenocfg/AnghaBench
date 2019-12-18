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
struct TYPE_6__ {int l; int r; int m; int wu; int wd; int whu; int whd; } ;
typedef  TYPE_1__ udev_input_mouse_t ;
struct TYPE_7__ {TYPE_1__ mouse; } ;
typedef  TYPE_2__ udev_input_device_t ;
struct input_event {int type; int value; int /*<<< orphan*/  code; } ;

/* Variables and functions */
#define  ABS_X 139 
#define  ABS_Y 138 
#define  BTN_LEFT 137 
#define  BTN_MIDDLE 136 
#define  BTN_RIGHT 135 
#define  EV_ABS 134 
#define  EV_KEY 133 
#define  EV_REL 132 
#define  REL_HWHEEL 131 
#define  REL_WHEEL 130 
#define  REL_X 129 
#define  REL_Y 128 
 int /*<<< orphan*/  udev_mouse_set_x (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  udev_mouse_set_y (TYPE_1__*,int,int) ; 

__attribute__((used)) static void udev_handle_mouse(void *data,
      const struct input_event *event, udev_input_device_t *dev)
{
   udev_input_mouse_t *mouse = &dev->mouse;

   switch (event->type)
   {
      case EV_KEY:
         switch (event->code)
         {
            case BTN_LEFT:
               mouse->l = event->value;
               break;

            case BTN_RIGHT:
               mouse->r = event->value;
               break;

            case BTN_MIDDLE:
               mouse->m = event->value;
               break;

            /*case BTN_??:
               mouse->b4 = event->value;
               break;*/

            /*case BTN_??:
               mouse->b5 = event->value;
               break;*/

            default:
               break;
         }
         break;

      case EV_REL:
         switch (event->code)
         {
            case REL_X:
               udev_mouse_set_x(mouse, event->value, false);
               break;
            case REL_Y:
               udev_mouse_set_y(mouse, event->value, false);
               break;
            case REL_WHEEL:
               if (event->value == 1)
                  mouse->wu = 1;
               else if (event->value == -1)
                  mouse->wd = 1;
               break;
            case REL_HWHEEL:
               if (event->value == 1)
                  mouse->whu = 1;
               else if (event->value == -1)
                  mouse->whd = 1;
               break;
         }
         break;

      case EV_ABS:
         switch (event->code)
         {
            case ABS_X:
               udev_mouse_set_x(mouse, event->value, true);
               break;
            case ABS_Y:
               udev_mouse_set_y(mouse, event->value, true);
               break;
         }
         break;
   }
}