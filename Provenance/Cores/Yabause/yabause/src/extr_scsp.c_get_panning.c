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

void get_panning(int pan, int * pan_val_l, int * pan_val_r)
{
   if (pan & 0x10)
   {
      //negative values
      *pan_val_l = 0;
      *pan_val_r = pan & 0xf;
   }
   else
   {
      *pan_val_l = pan & 0xf;
      *pan_val_r = 0;
   }
}