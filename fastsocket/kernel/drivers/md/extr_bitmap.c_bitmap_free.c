#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long pages; struct bitmap_page* bp; } ;
struct bitmap_page {struct bitmap_page* map; int /*<<< orphan*/  hijacked; TYPE_1__ counts; int /*<<< orphan*/  storage; int /*<<< orphan*/  pending_writes; int /*<<< orphan*/  write_wait; } ;
struct bitmap {struct bitmap* map; int /*<<< orphan*/  hijacked; TYPE_1__ counts; int /*<<< orphan*/  storage; int /*<<< orphan*/  pending_writes; int /*<<< orphan*/  write_wait; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_file_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bitmap_page*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bitmap_free(struct bitmap *bitmap)
{
	unsigned long k, pages;
	struct bitmap_page *bp;

	if (!bitmap) /* there was no bitmap */
		return;

	/* Shouldn't be needed - but just in case.... */
	wait_event(bitmap->write_wait,
		   atomic_read(&bitmap->pending_writes) == 0);

	/* release the bitmap file  */
	bitmap_file_unmap(&bitmap->storage);

	bp = bitmap->counts.bp;
	pages = bitmap->counts.pages;

	/* free all allocated memory */

	if (bp) /* deallocate the page memory */
		for (k = 0; k < pages; k++)
			if (bp[k].map && !bp[k].hijacked)
				kfree(bp[k].map);
	kfree(bp);
	kfree(bitmap);
}