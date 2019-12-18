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
 int /*<<< orphan*/  LHCALL_TS ; 
 int /*<<< orphan*/  X86_CR0_TS ; 
 int /*<<< orphan*/  current_cr0 ; 
 int /*<<< orphan*/  lazy_hcall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lguest_clts(void)
{
	lazy_hcall1(LHCALL_TS, 0);
	current_cr0 &= ~X86_CR0_TS;
}