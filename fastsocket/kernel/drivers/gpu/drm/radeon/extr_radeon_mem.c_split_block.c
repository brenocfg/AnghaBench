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
struct mem_block {int start; int size; struct drm_file* file_priv; struct mem_block* next; struct mem_block* prev; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mem_block* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mem_block *split_block(struct mem_block *p, int start, int size,
				     struct drm_file *file_priv)
{
	/* Maybe cut off the start of an existing block */
	if (start > p->start) {
		struct mem_block *newblock = kmalloc(sizeof(*newblock),
						     GFP_KERNEL);
		if (!newblock)
			goto out;
		newblock->start = start;
		newblock->size = p->size - (start - p->start);
		newblock->file_priv = NULL;
		newblock->next = p->next;
		newblock->prev = p;
		p->next->prev = newblock;
		p->next = newblock;
		p->size -= newblock->size;
		p = newblock;
	}

	/* Maybe cut off the end of an existing block */
	if (size < p->size) {
		struct mem_block *newblock = kmalloc(sizeof(*newblock),
						     GFP_KERNEL);
		if (!newblock)
			goto out;
		newblock->start = start + size;
		newblock->size = p->size - size;
		newblock->file_priv = NULL;
		newblock->next = p->next;
		newblock->prev = p;
		p->next->prev = newblock;
		p->next = newblock;
		p->size = size;
	}

      out:
	/* Our block is in the middle */
	p->file_priv = file_priv;
	return p;
}