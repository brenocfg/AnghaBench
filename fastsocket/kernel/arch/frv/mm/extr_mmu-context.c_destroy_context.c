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
struct TYPE_2__ {int id; int /*<<< orphan*/  id_link; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  TYPE_1__ mm_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_tlb_mm (int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxn_bitmap ; 
 int /*<<< orphan*/  cxn_owners_lock ; 
 int cxn_pinned ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void destroy_context(struct mm_struct *mm)
{
	mm_context_t *ctx = &mm->context;

	spin_lock(&cxn_owners_lock);

	if (!list_empty(&ctx->id_link)) {
		if (ctx->id == cxn_pinned)
			cxn_pinned = -1;

		list_del_init(&ctx->id_link);
		clear_bit(ctx->id, cxn_bitmap);
		__flush_tlb_mm(ctx->id);
		ctx->id = 0;
	}

	spin_unlock(&cxn_owners_lock);
}