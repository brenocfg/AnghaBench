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
struct TYPE_5__ {unsigned int pointer_count; TYPE_1__* pointer; } ;
typedef  TYPE_2__ qnx_input_t ;
typedef  int int16_t ;
struct TYPE_4__ {int full_x; int full_y; int x; int y; } ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_POINTER_PRESSED 130 
#define  RETRO_DEVICE_ID_POINTER_X 129 
#define  RETRO_DEVICE_ID_POINTER_Y 128 

__attribute__((used)) static int16_t qnx_pointer_input_state(qnx_input_t *qnx,
      unsigned idx, unsigned id, bool screen)
{
   int16_t x;
   int16_t y;

   if(screen)
   {
       x = qnx->pointer[idx].full_x;
       y = qnx->pointer[idx].full_y;
   }
   else
   {
       x = qnx->pointer[idx].x;
       y = qnx->pointer[idx].y;
   }

   switch (id)
   {
      case RETRO_DEVICE_ID_POINTER_X:
         return x;
      case RETRO_DEVICE_ID_POINTER_Y:
         return y;
      case RETRO_DEVICE_ID_POINTER_PRESSED:
         return (idx < qnx->pointer_count)
                 && (x != -0x8000)
                 && (y != -0x8000);
   }

   return 0;
}