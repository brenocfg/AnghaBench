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
struct wiiupro {int* hatvalue; } ;
struct hidpad_wiiupro_data {int /*<<< orphan*/  data; } ;
typedef  int int16_t ;

/* Variables and functions */
 int abs (int) ; 

__attribute__((used)) static int16_t hidpad_wiiupro_get_axis(void *data, unsigned axis)
{
#if 0
   struct hidpad_wiiupro_data *device = (struct hidpad_wiiupro_data*)data;
   struct wiiupro *rpt = device ? (struct wiiupro*)&device->data : NULL;

   if (device && (axis < 4))
   {
      int val = rpt ? rpt->hatvalue[axis] : 0;
      val = (val << 8) - 0x8000;
      return (abs(val) > 0x1000) ? val : 0;
   }
#endif

   return 0;
}