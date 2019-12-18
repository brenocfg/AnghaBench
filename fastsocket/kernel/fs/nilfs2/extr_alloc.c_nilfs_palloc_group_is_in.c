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
struct inode {int dummy; } ;
typedef  int __u64 ;

/* Variables and functions */
 int nilfs_palloc_entries_per_group (struct inode*) ; 

__attribute__((used)) static int
nilfs_palloc_group_is_in(struct inode *inode, unsigned long group, __u64 nr)
{
	__u64 first, last;

	first = group * nilfs_palloc_entries_per_group(inode);
	last = first + nilfs_palloc_entries_per_group(inode) - 1;
	return (nr >= first) && (nr <= last);
}