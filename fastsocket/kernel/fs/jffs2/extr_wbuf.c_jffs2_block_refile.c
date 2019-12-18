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
typedef  int uint32_t ;
struct jffs2_sb_info {int sector_size; int /*<<< orphan*/  dirty_size; int /*<<< orphan*/  wasted_size; int /*<<< orphan*/  nr_erasing_blocks; int /*<<< orphan*/  erase_pending_list; int /*<<< orphan*/  bad_used_list; struct jffs2_eraseblock* nextblock; } ;
struct jffs2_eraseblock {int offset; int free_size; int /*<<< orphan*/  dirty_size; int /*<<< orphan*/  wasted_size; int /*<<< orphan*/  list; scalar_t__ first_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  D1 (int /*<<< orphan*/ ) ; 
 int REFILE_NOTEMPTY ; 
 int REF_OBSOLETE ; 
 int /*<<< orphan*/  jffs2_dbg_acct_paranoia_check_nolock (struct jffs2_sb_info*,struct jffs2_eraseblock*) ; 
 int /*<<< orphan*/  jffs2_dbg_acct_sanity_check_nolock (struct jffs2_sb_info*,struct jffs2_eraseblock*) ; 
 int /*<<< orphan*/  jffs2_dbg_dump_block_lists_nolock (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_erase_pending_trigger (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_link_node_ref (struct jffs2_sb_info*,struct jffs2_eraseblock*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jffs2_prealloc_raw_node_refs (struct jffs2_sb_info*,struct jffs2_eraseblock*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static void jffs2_block_refile(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb, int allow_empty)
{
	D1(printk("About to refile bad block at %08x\n", jeb->offset));

	/* File the existing block on the bad_used_list.... */
	if (c->nextblock == jeb)
		c->nextblock = NULL;
	else /* Not sure this should ever happen... need more coffee */
		list_del(&jeb->list);
	if (jeb->first_node) {
		D1(printk("Refiling block at %08x to bad_used_list\n", jeb->offset));
		list_add(&jeb->list, &c->bad_used_list);
	} else {
		BUG_ON(allow_empty == REFILE_NOTEMPTY);
		/* It has to have had some nodes or we couldn't be here */
		D1(printk("Refiling block at %08x to erase_pending_list\n", jeb->offset));
		list_add(&jeb->list, &c->erase_pending_list);
		c->nr_erasing_blocks++;
		jffs2_erase_pending_trigger(c);
	}

	if (!jffs2_prealloc_raw_node_refs(c, jeb, 1)) {
		uint32_t oldfree = jeb->free_size;

		jffs2_link_node_ref(c, jeb, 
				    (jeb->offset+c->sector_size-oldfree) | REF_OBSOLETE,
				    oldfree, NULL);
		/* convert to wasted */
		c->wasted_size += oldfree;
		jeb->wasted_size += oldfree;
		c->dirty_size -= oldfree;
		jeb->dirty_size -= oldfree;
	}

	jffs2_dbg_dump_block_lists_nolock(c);
	jffs2_dbg_acct_sanity_check_nolock(c,jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);
}