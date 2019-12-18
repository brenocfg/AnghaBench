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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct qnx4_sb_info {struct qnx4_sb_info* BitMap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qnx4_sb_info*) ; 
 struct qnx4_sb_info* qnx4_sb (struct super_block*) ; 

__attribute__((used)) static void qnx4_put_super(struct super_block *sb)
{
	struct qnx4_sb_info *qs = qnx4_sb(sb);
	kfree( qs->BitMap );
	kfree( qs );
	sb->s_fs_info = NULL;
	return;
}