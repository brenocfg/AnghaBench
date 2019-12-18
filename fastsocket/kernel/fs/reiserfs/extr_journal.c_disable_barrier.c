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
struct super_block {int dummy; } ;
struct TYPE_2__ {int s_mount_opt; } ;

/* Variables and functions */
 int REISERFS_BARRIER_FLUSH ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_bdevname (struct super_block*) ; 

__attribute__((used)) static void disable_barrier(struct super_block *s)
{
	REISERFS_SB(s)->s_mount_opt &= ~(1 << REISERFS_BARRIER_FLUSH);
	printk("reiserfs: disabling flush barriers on %s\n",
	       reiserfs_bdevname(s));
}