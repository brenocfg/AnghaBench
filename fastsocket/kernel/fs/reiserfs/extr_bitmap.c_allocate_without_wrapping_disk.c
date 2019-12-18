#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  inode; TYPE_2__* th; int /*<<< orphan*/  block; int /*<<< orphan*/  formatted_node; } ;
typedef  TYPE_1__ reiserfs_blocknr_hint_t ;
typedef  scalar_t__ b_blocknr_t ;
struct TYPE_9__ {int i_prealloc_count; scalar_t__ i_prealloc_block; int /*<<< orphan*/  i_prealloc_list; } ;
struct TYPE_8__ {int /*<<< orphan*/  j_prealloc_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_super; } ;

/* Variables and functions */
 TYPE_5__* REISERFS_I (int /*<<< orphan*/ ) ; 
 TYPE_4__* SB_JOURNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int scan_bitmap (TYPE_2__*,scalar_t__*,scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int allocate_without_wrapping_disk(reiserfs_blocknr_hint_t * hint,
						 b_blocknr_t * new_blocknrs,
						 b_blocknr_t start,
						 b_blocknr_t finish, int min,
						 int amount_needed,
						 int prealloc_size)
{
	int rest = amount_needed;
	int nr_allocated;

	while (rest > 0 && start <= finish) {
		nr_allocated = scan_bitmap(hint->th, &start, finish, min,
					   rest + prealloc_size,
					   !hint->formatted_node, hint->block);

		if (nr_allocated == 0)	/* no new blocks allocated, return */
			break;

		/* fill free_blocknrs array first */
		while (rest > 0 && nr_allocated > 0) {
			*new_blocknrs++ = start++;
			rest--;
			nr_allocated--;
		}

		/* do we have something to fill prealloc. array also ? */
		if (nr_allocated > 0) {
			/* it means prealloc_size was greater that 0 and we do preallocation */
			list_add(&REISERFS_I(hint->inode)->i_prealloc_list,
				 &SB_JOURNAL(hint->th->t_super)->
				 j_prealloc_list);
			REISERFS_I(hint->inode)->i_prealloc_block = start;
			REISERFS_I(hint->inode)->i_prealloc_count =
			    nr_allocated;
			break;
		}
	}

	return (amount_needed - rest);
}