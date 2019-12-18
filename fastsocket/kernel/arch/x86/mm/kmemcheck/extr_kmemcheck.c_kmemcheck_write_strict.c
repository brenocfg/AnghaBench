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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmemcheck_save_addr (unsigned long) ; 
 void* kmemcheck_shadow_lookup (unsigned long) ; 
 int /*<<< orphan*/  kmemcheck_shadow_set (void*,unsigned int) ; 

__attribute__((used)) static void kmemcheck_write_strict(struct pt_regs *regs,
	unsigned long addr, unsigned int size)
{
	void *shadow;

	shadow = kmemcheck_shadow_lookup(addr);
	if (!shadow)
		return;

	kmemcheck_save_addr(addr);
	kmemcheck_shadow_set(shadow, size);
}