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
struct inotify_watch {TYPE_1__* inode; } ;
struct TYPE_2__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_super (struct super_block*) ; 
 int /*<<< orphan*/  put_inotify_watch (struct inotify_watch*) ; 

void unpin_inotify_watch(struct inotify_watch *watch)
{
	struct super_block *sb = watch->inode->i_sb;
	put_inotify_watch(watch);
	deactivate_super(sb);
}