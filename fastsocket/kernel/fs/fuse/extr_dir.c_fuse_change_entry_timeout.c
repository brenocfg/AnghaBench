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
struct fuse_entry_out {int /*<<< orphan*/  entry_valid_nsec; int /*<<< orphan*/  entry_valid; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_dentry_settime (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_to_jiffies (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fuse_change_entry_timeout(struct dentry *entry,
				      struct fuse_entry_out *o)
{
	fuse_dentry_settime(entry,
		time_to_jiffies(o->entry_valid, o->entry_valid_nsec));
}