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
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  consume_fifo (int /*<<< orphan*/ *,int) ; 
 int sh2_cycles_done_m68k (int /*<<< orphan*/ *) ; 

void p32x_pwm_sync_to_sh2(SH2 *sh2)
{
  int m68k_cycles = sh2_cycles_done_m68k(sh2);
  consume_fifo(sh2, m68k_cycles);
}