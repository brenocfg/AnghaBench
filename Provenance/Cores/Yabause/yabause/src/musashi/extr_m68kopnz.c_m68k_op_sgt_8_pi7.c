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
 scalar_t__ COND_GT () ; 
 int /*<<< orphan*/  EA_A7_PI_8 () ; 
 int /*<<< orphan*/  m68ki_write_8 (int /*<<< orphan*/ ,int) ; 

void m68k_op_sgt_8_pi7(void)
{
	m68ki_write_8(EA_A7_PI_8(), COND_GT() ? 0xff : 0);
}