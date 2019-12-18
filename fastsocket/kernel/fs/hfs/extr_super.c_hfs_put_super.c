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
 int /*<<< orphan*/  hfs_mdb_close (struct super_block*) ; 
 int /*<<< orphan*/  hfs_mdb_put (struct super_block*) ; 
 int /*<<< orphan*/  hfs_write_super (struct super_block*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void hfs_put_super(struct super_block *sb)
{
	lock_kernel();

	if (sb->s_dirt)
		hfs_write_super(sb);
	hfs_mdb_close(sb);
	/* release the MDB's resources */
	hfs_mdb_put(sb);

	unlock_kernel();
}