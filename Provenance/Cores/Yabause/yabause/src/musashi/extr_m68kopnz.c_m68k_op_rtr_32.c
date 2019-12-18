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
 int /*<<< orphan*/  m68ki_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_pull_16 () ; 
 int /*<<< orphan*/  m68ki_pull_32 () ; 
 int /*<<< orphan*/  m68ki_set_ccr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 

void m68k_op_rtr_32(void)
{
	m68ki_trace_t0();				   /* auto-disable (see m68kcpu.h) */
	m68ki_set_ccr(m68ki_pull_16());
	m68ki_jump(m68ki_pull_32());
}