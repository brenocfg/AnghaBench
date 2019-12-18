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
typedef  float int16_t ;
struct TYPE_4__ {float window_pos_x; float window_pos_y; } ;
typedef  TYPE_1__ cocoa_input_data_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 
 float cocoa_mouse_state (TYPE_1__*,unsigned int) ; 
 float get_backing_scale_factor () ; 

__attribute__((used)) static int16_t cocoa_mouse_state_screen(cocoa_input_data_t *apple,
                                        unsigned id)
{
   int16_t val;
#ifndef IOS
   float   backing_scale_factor = get_backing_scale_factor();
#endif

    switch (id)
    {
        case RETRO_DEVICE_ID_MOUSE_X:
            val = apple->window_pos_x;
            break;
        case RETRO_DEVICE_ID_MOUSE_Y:
            val = apple->window_pos_y;
            break;
        default:
            return cocoa_mouse_state(apple, id);
    }

#ifndef IOS
    val *= backing_scale_factor;
#endif
    return val;
}