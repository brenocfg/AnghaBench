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
 unsigned long X86_CR0_TS ; 
 unsigned long current_cr0 ; 
 int /*<<< orphan*/  lazy_hcall1 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void lguest_write_cr0(unsigned long val)
{
	lazy_hcall1(LHCALL_TS, val & X86_CR0_TS);
	current_cr0 = val;
}