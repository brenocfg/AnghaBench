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
struct TYPE_2__ {size_t page_id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 size_t INVALID_PAGEID ; 
 size_t NO_CONTEXT ; 
 int /*<<< orphan*/  flush_tlb_mm (struct mm_struct*) ; 
 size_t map_replace_ptr ; 
 struct mm_struct** page_id_map ; 
 int /*<<< orphan*/  printk (char*,size_t,struct mm_struct*) ; 

__attribute__((used)) static inline void
alloc_context(struct mm_struct *mm)
{
	struct mm_struct *old_mm;

	D(printk("tlb: alloc context %d (%p)\n", map_replace_ptr, mm));

	/* did we replace an mm ? */

	old_mm = page_id_map[map_replace_ptr];

	if(old_mm) {
		/* throw out any TLB entries belonging to the mm we replace
		 * in the map
		 */
		flush_tlb_mm(old_mm);

		old_mm->context.page_id = NO_CONTEXT;
	}

	/* insert it into the page_id_map */

	mm->context.page_id = map_replace_ptr;
	page_id_map[map_replace_ptr] = mm;

	map_replace_ptr++;

	if(map_replace_ptr == INVALID_PAGEID)
		map_replace_ptr = 0;         /* wrap around */	
}