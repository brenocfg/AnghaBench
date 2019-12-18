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
struct super_block {scalar_t__ s_dirt; } ;

/* Variables and functions */
 int fat_clusters_flush (struct super_block*) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static int fat_sync_fs(struct super_block *sb, int wait)
{
	int err = 0;

	if (sb->s_dirt) {
		lock_super(sb);
		sb->s_dirt = 0;
		err = fat_clusters_flush(sb);
		unlock_super(sb);
	}

	return err;
}