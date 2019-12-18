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
 scalar_t__ COND_LT () ; 
 int /*<<< orphan*/  EA_AY_PD_8 () ; 
 int /*<<< orphan*/  m68ki_write_8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void m68k_op_slt_8_pd(void)
{
  m68ki_write_8(EA_AY_PD_8(), COND_LT() ? 0xff : 0);
}