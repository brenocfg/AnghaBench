#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {TYPE_1__* vfs_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeback_inodes_sb (TYPE_1__*) ; 

__attribute__((used)) static void shrink_liability(struct ubifs_info *c, int nr_to_write)
{
	down_read(&c->vfs_sb->s_umount);
	writeback_inodes_sb(c->vfs_sb);
	up_read(&c->vfs_sb->s_umount);
}