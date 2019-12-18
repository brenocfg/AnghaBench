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
 int /*<<< orphan*/ * REG_A ; 
 int /*<<< orphan*/  m68ki_read_32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_unlk_32_a7(void)
{
  REG_A[7] = m68ki_read_32(REG_A[7]);
}