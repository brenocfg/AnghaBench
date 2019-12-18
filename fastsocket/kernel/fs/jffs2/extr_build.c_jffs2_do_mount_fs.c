#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct jffs2_sb_info {int free_size; int flash_size; int nr_blocks; int sector_size; int highest_ino; TYPE_1__* blocks; int /*<<< orphan*/ * summary; int /*<<< orphan*/  bad_used_list; int /*<<< orphan*/  bad_list; int /*<<< orphan*/  free_list; int /*<<< orphan*/  erase_complete_list; int /*<<< orphan*/  erasable_pending_wbuf_list; int /*<<< orphan*/  erase_pending_list; int /*<<< orphan*/  erase_checking_list; int /*<<< orphan*/  erasing_list; int /*<<< orphan*/  erasable_list; int /*<<< orphan*/  dirty_list; int /*<<< orphan*/  very_dirty_list; int /*<<< orphan*/  clean_list; } ;
struct jffs2_eraseblock {int dummy; } ;
struct TYPE_6__ {int offset; int free_size; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_fsbuild (char*) ; 
 scalar_t__ jffs2_blocks_use_vmalloc (struct jffs2_sb_info*) ; 
 scalar_t__ jffs2_build_filesystem (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_calc_trigger_levels (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_free_ino_caches (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_free_raw_node_refs (struct jffs2_sb_info*) ; 
 int jffs2_sum_init (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfree (TYPE_1__*) ; 
 TYPE_1__* vmalloc (int) ; 

int jffs2_do_mount_fs(struct jffs2_sb_info *c)
{
	int ret;
	int i;
	int size;

	c->free_size = c->flash_size;
	c->nr_blocks = c->flash_size / c->sector_size;
	size = sizeof(struct jffs2_eraseblock) * c->nr_blocks;
#ifndef __ECOS
	if (jffs2_blocks_use_vmalloc(c))
		c->blocks = vmalloc(size);
	else
#endif
		c->blocks = kmalloc(size, GFP_KERNEL);
	if (!c->blocks)
		return -ENOMEM;

	memset(c->blocks, 0, size);
	for (i=0; i<c->nr_blocks; i++) {
		INIT_LIST_HEAD(&c->blocks[i].list);
		c->blocks[i].offset = i * c->sector_size;
		c->blocks[i].free_size = c->sector_size;
	}

	INIT_LIST_HEAD(&c->clean_list);
	INIT_LIST_HEAD(&c->very_dirty_list);
	INIT_LIST_HEAD(&c->dirty_list);
	INIT_LIST_HEAD(&c->erasable_list);
	INIT_LIST_HEAD(&c->erasing_list);
	INIT_LIST_HEAD(&c->erase_checking_list);
	INIT_LIST_HEAD(&c->erase_pending_list);
	INIT_LIST_HEAD(&c->erasable_pending_wbuf_list);
	INIT_LIST_HEAD(&c->erase_complete_list);
	INIT_LIST_HEAD(&c->free_list);
	INIT_LIST_HEAD(&c->bad_list);
	INIT_LIST_HEAD(&c->bad_used_list);
	c->highest_ino = 1;
	c->summary = NULL;

	ret = jffs2_sum_init(c);
	if (ret)
		goto out_free;

	if (jffs2_build_filesystem(c)) {
		dbg_fsbuild("build_fs failed\n");
		jffs2_free_ino_caches(c);
		jffs2_free_raw_node_refs(c);
		ret = -EIO;
		goto out_free;
	}

	jffs2_calc_trigger_levels(c);

	return 0;

 out_free:
#ifndef __ECOS
	if (jffs2_blocks_use_vmalloc(c))
		vfree(c->blocks);
	else
#endif
		kfree(c->blocks);

	return ret;
}