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
typedef  enum kmemcheck_shadow { ____Placeholder_kmemcheck_shadow } kmemcheck_shadow ;

/* Variables and functions */
 int KMEMCHECK_SHADOW_INITIALIZED ; 
 int kmemcheck_enabled ; 
 int /*<<< orphan*/  kmemcheck_error_save (int,unsigned long,unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/  kmemcheck_save_addr (unsigned long) ; 
 void* kmemcheck_shadow_lookup (unsigned long) ; 
 int /*<<< orphan*/  kmemcheck_shadow_set (void*,unsigned int) ; 
 int kmemcheck_shadow_test (void*,unsigned int) ; 

__attribute__((used)) static void kmemcheck_read_strict(struct pt_regs *regs,
	unsigned long addr, unsigned int size)
{
	void *shadow;
	enum kmemcheck_shadow status;

	shadow = kmemcheck_shadow_lookup(addr);
	if (!shadow)
		return;

	kmemcheck_save_addr(addr);
	status = kmemcheck_shadow_test(shadow, size);
	if (status == KMEMCHECK_SHADOW_INITIALIZED)
		return;

	if (kmemcheck_enabled)
		kmemcheck_error_save(status, addr, size, regs);

	if (kmemcheck_enabled == 2)
		kmemcheck_enabled = 0;

	/* Don't warn about it again. */
	kmemcheck_shadow_set(shadow, size);
}