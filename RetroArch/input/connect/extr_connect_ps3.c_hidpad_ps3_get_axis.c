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
struct hidpad_ps3_data {int* data; } ;
typedef  int int16_t ;

/* Variables and functions */
 int abs (int) ; 

__attribute__((used)) static int16_t hidpad_ps3_get_axis(void *data, unsigned axis)
{
   int val;
   struct hidpad_ps3_data *device = (struct hidpad_ps3_data*)data;

   if (!device || axis >= 4)
      return 0;

   val = device->data[7 + axis];
   val = (val << 8) - 0x8000;

   return (abs(val) > 0x1000) ? val : 0;
}