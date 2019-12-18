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
struct memory_bitmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PG_UNSAFE_CLEAR ; 
 struct memory_bitmap* forbidden_pages_map ; 
 struct memory_bitmap* free_pages_map ; 
 int /*<<< orphan*/  kfree (struct memory_bitmap*) ; 
 int /*<<< orphan*/  memory_bm_free (struct memory_bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void free_basic_memory_bitmaps(void)
{
	struct memory_bitmap *bm1, *bm2;

	BUG_ON(!(forbidden_pages_map && free_pages_map));

	bm1 = forbidden_pages_map;
	bm2 = free_pages_map;
	forbidden_pages_map = NULL;
	free_pages_map = NULL;
	memory_bm_free(bm1, PG_UNSAFE_CLEAR);
	kfree(bm1);
	memory_bm_free(bm2, PG_UNSAFE_CLEAR);
	kfree(bm2);

	pr_debug("PM: Basic memory bitmaps freed\n");
}