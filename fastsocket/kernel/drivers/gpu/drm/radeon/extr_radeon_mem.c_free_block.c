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
struct mem_block {struct mem_block* prev; struct mem_block* next; scalar_t__ size; int /*<<< orphan*/ * file_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mem_block*) ; 

__attribute__((used)) static void free_block(struct mem_block *p)
{
	p->file_priv = NULL;

	/* Assumes a single contiguous range.  Needs a special file_priv in
	 * 'heap' to stop it being subsumed.
	 */
	if (p->next->file_priv == NULL) {
		struct mem_block *q = p->next;
		p->size += q->size;
		p->next = q->next;
		p->next->prev = p;
		kfree(q);
	}

	if (p->prev->file_priv == NULL) {
		struct mem_block *q = p->prev;
		q->size += p->size;
		q->next = p->next;
		q->next->prev = q;
		kfree(p);
	}
}