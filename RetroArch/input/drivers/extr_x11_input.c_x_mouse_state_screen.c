#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mouse_y; int /*<<< orphan*/  mouse_x; } ;
typedef  TYPE_1__ x11_input_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 
 int /*<<< orphan*/  x_mouse_state (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int16_t x_mouse_state_screen(x11_input_t *x11, unsigned id)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
         return x11->mouse_x;
      case RETRO_DEVICE_ID_MOUSE_Y:
         return x11->mouse_y;
      default:
         break;
   }

   return x_mouse_state(x11, id);
}