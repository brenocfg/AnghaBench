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
typedef  int /*<<< orphan*/  smpfunc_t ;

/* Variables and functions */
 scalar_t__ BTFIXUP_CALL (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  xc0 (int /*<<< orphan*/ ) ; 

void smp_flush_tlb_all(void)
{
	xc0((smpfunc_t) BTFIXUP_CALL(local_flush_tlb_all));
	local_flush_tlb_all();
}