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
 unsigned long X86_CR4_OSXSAVE ; 
 unsigned long X86_CR4_PGE ; 
 unsigned long X86_CR4_PSE ; 
 int /*<<< orphan*/  native_write_cr4 (unsigned long) ; 

__attribute__((used)) static void xen_write_cr4(unsigned long cr4)
{
	cr4 &= ~X86_CR4_PGE;
	cr4 &= ~X86_CR4_PSE;
	cr4 &= ~X86_CR4_OSXSAVE;

	native_write_cr4(cr4);
}