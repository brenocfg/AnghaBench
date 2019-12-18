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
struct super_block {int dummy; } ;
struct jffs2_sb_info {int /*<<< orphan*/  alloc_sem; } ;

/* Variables and functions */
 struct jffs2_sb_info* JFFS2_SB_INFO (struct super_block*) ; 
 int /*<<< orphan*/  jffs2_flush_wbuf_pad (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_write_super (struct super_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jffs2_sync_fs(struct super_block *sb, int wait)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(sb);

	jffs2_write_super(sb);

	mutex_lock(&c->alloc_sem);
	jffs2_flush_wbuf_pad(c);
	mutex_unlock(&c->alloc_sem);
	return 0;
}