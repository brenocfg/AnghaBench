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
typedef  int u64 ;
struct dentry {int d_time; void* d_fsdata; } ;

/* Variables and functions */

__attribute__((used)) static void fuse_dentry_settime(struct dentry *entry, u64 time)
{
	entry->d_time = time;
	entry->d_fsdata = (void *) (unsigned long) (time >> 32);
}