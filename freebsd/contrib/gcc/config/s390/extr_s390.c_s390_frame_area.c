#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int first_restore_gpr; int gprs_offset; int last_restore_gpr; int high_fprs; scalar_t__ f4_offset; scalar_t__ f8_offset; } ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 int MAX (int,scalar_t__) ; 
 int MIN (int,scalar_t__) ; 
 scalar_t__ TARGET_64BIT ; 
 int UNITS_PER_WORD ; 
 scalar_t__ cfun_fpr_bit_p (int) ; 
 TYPE_1__ cfun_frame_layout ; 
 scalar_t__ cfun_save_high_fprs_p ; 

__attribute__((used)) static void
s390_frame_area (int *area_bottom, int *area_top)
{
  int b, t;
  int i;

  b = INT_MAX;
  t = INT_MIN;

  if (cfun_frame_layout.first_restore_gpr != -1)
    {
      b = (cfun_frame_layout.gprs_offset
	   + cfun_frame_layout.first_restore_gpr * UNITS_PER_WORD);
      t = b + (cfun_frame_layout.last_restore_gpr
	       - cfun_frame_layout.first_restore_gpr + 1) * UNITS_PER_WORD;
    }

  if (TARGET_64BIT && cfun_save_high_fprs_p)
    {
      b = MIN (b, cfun_frame_layout.f8_offset);
      t = MAX (t, (cfun_frame_layout.f8_offset
		   + cfun_frame_layout.high_fprs * 8));
    }

  if (!TARGET_64BIT)
    for (i = 2; i < 4; i++)
      if (cfun_fpr_bit_p (i))
	{
	  b = MIN (b, cfun_frame_layout.f4_offset + (i - 2) * 8);
	  t = MAX (t, cfun_frame_layout.f4_offset + (i - 1) * 8);
	}
  
  *area_bottom = b;
  *area_top = t;
}