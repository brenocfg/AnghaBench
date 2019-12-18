#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ s16 ;
struct TYPE_3__ {int systemclipY2; scalar_t__ systemclipX2; } ;
typedef  TYPE_1__ Vdp1 ;

/* Variables and functions */
 scalar_t__ vdp1interlace ; 

int is_pre_clipped(s16 tl_x, s16 tl_y, s16 bl_x, s16 bl_y, s16 tr_x, s16 tr_y, s16 br_x, s16 br_y, Vdp1* regs)
{
   int y_val = regs->systemclipY2;

   if (vdp1interlace)
      y_val *= 2;

   //if all x values are to the left of the screen
   if ((tl_x < 0) &&
      (bl_x < 0) &&
      (tr_x < 0) &&
      (br_x < 0))
      return 1;

   //to the right
   if ((tl_x > regs->systemclipX2) &&
      (bl_x > regs->systemclipX2) &&
      (tr_x > regs->systemclipX2) &&
      (br_x > regs->systemclipX2))
      return 1;

   //above
   if ((tl_y < 0) &&
      (bl_y < 0) &&
      (tr_y < 0) &&
      (br_y < 0))
      return 1;

   //below
   if ((tl_y > y_val) &&
      (bl_y > y_val) &&
      (tr_y > y_val) &&
      (br_y > y_val))
      return 1;

   return 0;
}