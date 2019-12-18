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
typedef  int uint8_t ;
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  shadow ;
typedef  enum kmemcheck_shadow { ____Placeholder_kmemcheck_shadow } kmemcheck_shadow ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int KMEMCHECK_SHADOW_INITIALIZED ; 
 unsigned long PAGE_MASK ; 
 int kmemcheck_enabled ; 
 int /*<<< orphan*/  kmemcheck_error_save (int,unsigned long,unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/  kmemcheck_save_addr (unsigned long) ; 
 int* kmemcheck_shadow_lookup (unsigned long) ; 
 int kmemcheck_shadow_test (int*,unsigned int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void kmemcheck_copy(struct pt_regs *regs,
	unsigned long src_addr, unsigned long dst_addr, unsigned int size)
{
	uint8_t shadow[8];
	enum kmemcheck_shadow status;

	unsigned long page;
	unsigned long next_addr;
	unsigned long next_page;

	uint8_t *x;
	unsigned int i;
	unsigned int n;

	BUG_ON(size > sizeof(shadow));

	page = src_addr & PAGE_MASK;
	next_addr = src_addr + size - 1;
	next_page = next_addr & PAGE_MASK;

	if (likely(page == next_page)) {
		/* Same page */
		x = kmemcheck_shadow_lookup(src_addr);
		if (x) {
			kmemcheck_save_addr(src_addr);
			for (i = 0; i < size; ++i)
				shadow[i] = x[i];
		} else {
			for (i = 0; i < size; ++i)
				shadow[i] = KMEMCHECK_SHADOW_INITIALIZED;
		}
	} else {
		n = next_page - src_addr;
		BUG_ON(n > sizeof(shadow));

		/* First page */
		x = kmemcheck_shadow_lookup(src_addr);
		if (x) {
			kmemcheck_save_addr(src_addr);
			for (i = 0; i < n; ++i)
				shadow[i] = x[i];
		} else {
			/* Not tracked */
			for (i = 0; i < n; ++i)
				shadow[i] = KMEMCHECK_SHADOW_INITIALIZED;
		}

		/* Second page */
		x = kmemcheck_shadow_lookup(next_page);
		if (x) {
			kmemcheck_save_addr(next_page);
			for (i = n; i < size; ++i)
				shadow[i] = x[i - n];
		} else {
			/* Not tracked */
			for (i = n; i < size; ++i)
				shadow[i] = KMEMCHECK_SHADOW_INITIALIZED;
		}
	}

	page = dst_addr & PAGE_MASK;
	next_addr = dst_addr + size - 1;
	next_page = next_addr & PAGE_MASK;

	if (likely(page == next_page)) {
		/* Same page */
		x = kmemcheck_shadow_lookup(dst_addr);
		if (x) {
			kmemcheck_save_addr(dst_addr);
			for (i = 0; i < size; ++i) {
				x[i] = shadow[i];
				shadow[i] = KMEMCHECK_SHADOW_INITIALIZED;
			}
		}
	} else {
		n = next_page - dst_addr;
		BUG_ON(n > sizeof(shadow));

		/* First page */
		x = kmemcheck_shadow_lookup(dst_addr);
		if (x) {
			kmemcheck_save_addr(dst_addr);
			for (i = 0; i < n; ++i) {
				x[i] = shadow[i];
				shadow[i] = KMEMCHECK_SHADOW_INITIALIZED;
			}
		}

		/* Second page */
		x = kmemcheck_shadow_lookup(next_page);
		if (x) {
			kmemcheck_save_addr(next_page);
			for (i = n; i < size; ++i) {
				x[i - n] = shadow[i];
				shadow[i] = KMEMCHECK_SHADOW_INITIALIZED;
			}
		}
	}

	status = kmemcheck_shadow_test(shadow, size);
	if (status == KMEMCHECK_SHADOW_INITIALIZED)
		return;

	if (kmemcheck_enabled)
		kmemcheck_error_save(status, src_addr, size, regs);

	if (kmemcheck_enabled == 2)
		kmemcheck_enabled = 0;
}