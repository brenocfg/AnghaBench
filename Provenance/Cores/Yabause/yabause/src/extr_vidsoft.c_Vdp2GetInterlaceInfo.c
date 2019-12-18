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
 scalar_t__ vdp2_interlace ; 
 scalar_t__ vdp2_is_odd_frame ; 

void Vdp2GetInterlaceInfo(int * start_line, int * line_increment)
{
   if (vdp2_interlace)
   {
      if (vdp2_is_odd_frame)
      {
         *start_line = 1;
      }
      else
      {
         *start_line = 0;
      }

      *line_increment = 2;
   }
   else
   {
      *start_line = 0;
      *line_increment = 1;
   }
}