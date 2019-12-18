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
struct slob_page {int units; void* free; } ;
typedef  int slobidx_t ;
typedef  void slob_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SIZE ; 
 int SLOB_UNITS (int) ; 
 int /*<<< orphan*/  ZERO_OR_NULL_PTR (void*) ; 
 int /*<<< orphan*/  clear_slob_page (struct slob_page*) ; 
 int /*<<< orphan*/  clear_slob_page_free (struct slob_page*) ; 
 int /*<<< orphan*/  free_slob_page (struct slob_page*) ; 
 int /*<<< orphan*/  free_slob_small ; 
 int /*<<< orphan*/  set_slob (void*,int,void*) ; 
 int /*<<< orphan*/  set_slob_page_free (struct slob_page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slob_free_pages (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slob_last (void*) ; 
 int /*<<< orphan*/  slob_lock ; 
 void* slob_next (void*) ; 
 struct slob_page* slob_page (void*) ; 
 scalar_t__ slob_page_free (struct slob_page*) ; 
 int slob_units (void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slob_free(void *block, int size)
{
	struct slob_page *sp;
	slob_t *prev, *next, *b = (slob_t *)block;
	slobidx_t units;
	unsigned long flags;

	if (unlikely(ZERO_OR_NULL_PTR(block)))
		return;
	BUG_ON(!size);

	sp = slob_page(block);
	units = SLOB_UNITS(size);

	spin_lock_irqsave(&slob_lock, flags);

	if (sp->units + units == SLOB_UNITS(PAGE_SIZE)) {
		/* Go directly to page allocator. Do not pass slob allocator */
		if (slob_page_free(sp))
			clear_slob_page_free(sp);
		spin_unlock_irqrestore(&slob_lock, flags);
		clear_slob_page(sp);
		free_slob_page(sp);
		slob_free_pages(b, 0);
		return;
	}

	if (!slob_page_free(sp)) {
		/* This slob page is about to become partially free. Easy! */
		sp->units = units;
		sp->free = b;
		set_slob(b, units,
			(void *)((unsigned long)(b +
					SLOB_UNITS(PAGE_SIZE)) & PAGE_MASK));
		set_slob_page_free(sp, &free_slob_small);
		goto out;
	}

	/*
	 * Otherwise the page is already partially free, so find reinsertion
	 * point.
	 */
	sp->units += units;

	if (b < sp->free) {
		if (b + units == sp->free) {
			units += slob_units(sp->free);
			sp->free = slob_next(sp->free);
		}
		set_slob(b, units, sp->free);
		sp->free = b;
	} else {
		prev = sp->free;
		next = slob_next(prev);
		while (b > next) {
			prev = next;
			next = slob_next(prev);
		}

		if (!slob_last(prev) && b + units == next) {
			units += slob_units(next);
			set_slob(b, units, slob_next(next));
		} else
			set_slob(b, units, next);

		if (prev + slob_units(prev) == b) {
			units = slob_units(b) + slob_units(prev);
			set_slob(prev, units, slob_next(b));
		} else
			set_slob(prev, slob_units(prev), b);
	}
out:
	spin_unlock_irqrestore(&slob_lock, flags);
}