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
struct jffs2_sb_info {int /*<<< orphan*/  dirty_list; int /*<<< orphan*/  very_dirty_list; int /*<<< orphan*/  wasted_size; int /*<<< orphan*/  dirty_size; } ;
struct jffs2_eraseblock {int /*<<< orphan*/  list; int /*<<< orphan*/  dirty_size; scalar_t__ wasted_size; int /*<<< orphan*/  free_size; } ;

/* Variables and functions */
 scalar_t__ VERYDIRTY (struct jffs2_sb_info*,int /*<<< orphan*/ ) ; 
 int jffs2_prealloc_raw_node_refs (struct jffs2_sb_info*,struct jffs2_eraseblock*,int) ; 
 int jffs2_scan_dirty_space (struct jffs2_sb_info*,struct jffs2_eraseblock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int file_dirty(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb)
{
	int ret;

	if ((ret = jffs2_prealloc_raw_node_refs(c, jeb, 1)))
		return ret;
	if ((ret = jffs2_scan_dirty_space(c, jeb, jeb->free_size)))
		return ret;
	/* Turned wasted size into dirty, since we apparently 
	   think it's recoverable now. */
	jeb->dirty_size += jeb->wasted_size;
	c->dirty_size += jeb->wasted_size;
	c->wasted_size -= jeb->wasted_size;
	jeb->wasted_size = 0;
	if (VERYDIRTY(c, jeb->dirty_size)) {
		list_add(&jeb->list, &c->very_dirty_list);
	} else {
		list_add(&jeb->list, &c->dirty_list);
	}
	return 0;
}