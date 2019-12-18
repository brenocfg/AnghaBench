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
 int /*<<< orphan*/  X86_CR4_PCE ; 
 int /*<<< orphan*/  clear_in_cr4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_in_cr4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void change_rdpmc(void *info)
{
	bool enable = !!(unsigned long)info;

	if (enable)
		set_in_cr4(X86_CR4_PCE);
	else
		clear_in_cr4(X86_CR4_PCE);
}