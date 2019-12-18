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
 int /*<<< orphan*/  HOOK_MEM_BASE_ADDR ; 
 int /*<<< orphan*/  hook_base ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hook_init(void)
{
	static int first = 1;
	if (first) {
		first = 0;
		hook_base = ioremap(HOOK_MEM_BASE_ADDR, 8192);
	}
}