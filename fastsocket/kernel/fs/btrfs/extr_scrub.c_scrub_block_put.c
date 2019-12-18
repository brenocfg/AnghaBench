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
struct scrub_block {int page_count; TYPE_1__* pagev; int /*<<< orphan*/  ref_count; } ;
struct TYPE_2__ {scalar_t__ page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct scrub_block*) ; 

__attribute__((used)) static void scrub_block_put(struct scrub_block *sblock)
{
	if (atomic_dec_and_test(&sblock->ref_count)) {
		int i;

		for (i = 0; i < sblock->page_count; i++)
			if (sblock->pagev[i].page)
				__free_page(sblock->pagev[i].page);
		kfree(sblock);
	}
}