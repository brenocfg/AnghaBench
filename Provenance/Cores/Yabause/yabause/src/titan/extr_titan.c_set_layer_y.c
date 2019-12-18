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

void set_layer_y(const int start_line, int * layer_y)
{
   if (vdp2_interlace)
      *layer_y = start_line / 2;
   else
      *layer_y = start_line;
}