#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct frame {unsigned int level; TYPE_2__* n; scalar_t__ current_child; void* nr_children; int /*<<< orphan*/  b; } ;
struct del_stack {int top; int /*<<< orphan*/  info; int /*<<< orphan*/  tm; struct frame* spine; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  nr_entries; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENOMEM ; 
 int INTERNAL_NODE ; 
 int MAX_SPINE_DEPTH ; 
 int /*<<< orphan*/  btree_node_validator ; 
 TYPE_2__* dm_block_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dm_tm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_tm_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ is_internal_level (int /*<<< orphan*/ ,struct frame*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch_children (struct del_stack*,struct frame*) ; 

__attribute__((used)) static int push_frame(struct del_stack *s, dm_block_t b, unsigned level)
{
	int r;
	uint32_t ref_count;

	if (s->top >= MAX_SPINE_DEPTH - 1) {
		DMERR("btree deletion stack out of memory");
		return -ENOMEM;
	}

	r = dm_tm_ref(s->tm, b, &ref_count);
	if (r)
		return r;

	if (ref_count > 1)
		/*
		 * This is a shared node, so we can just decrement it's
		 * reference counter and leave the children.
		 */
		dm_tm_dec(s->tm, b);

	else {
		uint32_t flags;
		struct frame *f = s->spine + ++s->top;

		r = dm_tm_read_lock(s->tm, b, &btree_node_validator, &f->b);
		if (r) {
			s->top--;
			return r;
		}

		f->n = dm_block_data(f->b);
		f->level = level;
		f->nr_children = le32_to_cpu(f->n->header.nr_entries);
		f->current_child = 0;

		flags = le32_to_cpu(f->n->header.flags);
		if (flags & INTERNAL_NODE || is_internal_level(s->info, f))
			prefetch_children(s, f);
	}

	return 0;
}