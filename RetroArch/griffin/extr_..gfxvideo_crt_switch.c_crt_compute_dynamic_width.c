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

/* Variables and functions */
 int p_clock ; 
 int ra_core_hz ; 

int crt_compute_dynamic_width(int width)
{
   unsigned i;
   int dynamic_width   = 0;
   unsigned min_height = 261;

#if defined(HAVE_VIDEOCORE)
   p_clock             = 32000000;
#else
   p_clock             = 21000000;
#endif

   for (i = 0; i < 10; i++)
   {
      dynamic_width = width*i;
      if ((dynamic_width * min_height * ra_core_hz) > p_clock)
         break;

   }
   return dynamic_width;
}