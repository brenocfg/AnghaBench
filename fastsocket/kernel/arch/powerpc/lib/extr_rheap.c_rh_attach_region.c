#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int alignment; } ;
typedef  TYPE_1__ rh_info_t ;
struct TYPE_10__ {unsigned long start; int size; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_2__ rh_block_t ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 int assure_empty (TYPE_1__*,int) ; 
 int /*<<< orphan*/  attach_free_block (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* get_slot (TYPE_1__*) ; 

int rh_attach_region(rh_info_t * info, unsigned long start, int size)
{
	rh_block_t *blk;
	unsigned long s, e, m;
	int r;

	/* The region must be aligned */
	s = start;
	e = s + size;
	m = info->alignment - 1;

	/* Round start up */
	s = (s + m) & ~m;

	/* Round end down */
	e = e & ~m;

	if (IS_ERR_VALUE(e) || (e < s))
		return -ERANGE;

	/* Take final values */
	start = s;
	size = e - s;

	/* Grow the blocks, if needed */
	r = assure_empty(info, 1);
	if (r < 0)
		return r;

	blk = get_slot(info);
	blk->start = start;
	blk->size = size;
	blk->owner = NULL;

	attach_free_block(info, blk);

	return 0;
}