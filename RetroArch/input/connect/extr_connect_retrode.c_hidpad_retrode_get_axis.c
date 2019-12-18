#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hidpad_retrode_data {int* data; } ;
typedef  int int16_t ;

/* Variables and functions */
 int abs (int) ; 

__attribute__((used)) static int16_t hidpad_retrode_get_axis(void *data, unsigned axis)
{
   int val;
   struct hidpad_retrode_data *device = (struct hidpad_retrode_data*)data;

   if (!device || axis >= 2)
      return 0;

   val = device->data[2 + axis];

   /* map Retrode values to a known gamepad (VID=0x0079, PID=0x0011) */
   if (val == 0x9C)
       val = 0x00; /* axis=0 left, axis=1 up */
   else if (val == 0x64)
       val = 0xFF; /* axis=0 right, axis=1 down */
   else
       val = 0x7F; /* no button pressed */

   val = (val << 8) - 0x8000;

   return (abs(val) > 0x1000) ? val : 0;
}