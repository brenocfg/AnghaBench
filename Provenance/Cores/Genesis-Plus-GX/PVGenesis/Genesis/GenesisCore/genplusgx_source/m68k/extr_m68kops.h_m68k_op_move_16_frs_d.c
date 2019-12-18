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
 int DY ; 
 int MASK_OUT_BELOW_16 (int) ; 
 int m68ki_get_sr () ; 

__attribute__((used)) static void m68k_op_move_16_frs_d(void)
{
  DY = MASK_OUT_BELOW_16(DY) | m68ki_get_sr();
}