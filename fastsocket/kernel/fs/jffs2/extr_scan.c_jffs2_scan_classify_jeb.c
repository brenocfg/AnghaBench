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
struct jffs2_sb_info {scalar_t__ sector_size; int /*<<< orphan*/  wasted_size; int /*<<< orphan*/  dirty_size; int /*<<< orphan*/  cleanmarker_size; } ;
struct jffs2_eraseblock {scalar_t__ used_size; scalar_t__ unchecked_size; scalar_t__ dirty_size; int /*<<< orphan*/  wasted_size; int /*<<< orphan*/  first_node; } ;

/* Variables and functions */
 int BLK_STATE_ALLDIRTY ; 
 int BLK_STATE_CLEAN ; 
 int BLK_STATE_CLEANMARKER ; 
 int BLK_STATE_PARTDIRTY ; 
 int /*<<< orphan*/  ISDIRTY (scalar_t__) ; 
 scalar_t__ PAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_next (int /*<<< orphan*/ ) ; 

int jffs2_scan_classify_jeb(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb)
{
	if ((jeb->used_size + jeb->unchecked_size) == PAD(c->cleanmarker_size) && !jeb->dirty_size
	    && (!jeb->first_node || !ref_next(jeb->first_node)) )
		return BLK_STATE_CLEANMARKER;

	/* move blocks with max 4 byte dirty space to cleanlist */
	else if (!ISDIRTY(c->sector_size - (jeb->used_size + jeb->unchecked_size))) {
		c->dirty_size -= jeb->dirty_size;
		c->wasted_size += jeb->dirty_size;
		jeb->wasted_size += jeb->dirty_size;
		jeb->dirty_size = 0;
		return BLK_STATE_CLEAN;
	} else if (jeb->used_size || jeb->unchecked_size)
		return BLK_STATE_PARTDIRTY;
	else
		return BLK_STATE_ALLDIRTY;
}