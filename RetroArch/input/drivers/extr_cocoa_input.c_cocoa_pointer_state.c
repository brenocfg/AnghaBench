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
struct TYPE_4__ {int fixed_x; int fixed_y; int full_x; int full_y; } ;
typedef  TYPE_1__ cocoa_touch_data_t ;
struct TYPE_5__ {unsigned int touch_count; int /*<<< orphan*/ * touches; } ;
typedef  TYPE_2__ cocoa_input_data_t ;

/* Variables and functions */
 unsigned int MAX_TOUCHES ; 
 unsigned int RARCH_DEVICE_POINTER_SCREEN ; 
#define  RETRO_DEVICE_ID_POINTER_COUNT 131 
#define  RETRO_DEVICE_ID_POINTER_PRESSED 130 
#define  RETRO_DEVICE_ID_POINTER_X 129 
#define  RETRO_DEVICE_ID_POINTER_Y 128 

__attribute__((used)) static int16_t cocoa_pointer_state(cocoa_input_data_t *apple,
      unsigned device, unsigned idx, unsigned id)
{
   const bool want_full = (device == RARCH_DEVICE_POINTER_SCREEN);

   if (idx < apple->touch_count && (idx < MAX_TOUCHES))
   {
      int16_t x, y;
      const cocoa_touch_data_t *touch = (const cocoa_touch_data_t *)
         &apple->touches[idx];

       if (!touch)
           return 0;

      x = touch->fixed_x;
      y = touch->fixed_y;

      if (want_full)
      {
         x = touch->full_x;
         y = touch->full_y;
      }

      switch (id)
      {
         case RETRO_DEVICE_ID_POINTER_PRESSED:
            return (x != -0x8000) && (y != -0x8000);
         case RETRO_DEVICE_ID_POINTER_X:
            return x;
         case RETRO_DEVICE_ID_POINTER_Y:
            return y;
         case RETRO_DEVICE_ID_POINTER_COUNT:
            return apple->touch_count;
      }
   }

   return 0;
}