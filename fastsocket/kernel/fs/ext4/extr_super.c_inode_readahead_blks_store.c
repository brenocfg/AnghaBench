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
struct ext4_sb_info {unsigned long s_inode_readahead_blks; } ;
struct ext4_attr {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 scalar_t__ parse_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t inode_readahead_blks_store(struct ext4_attr *a,
					  struct ext4_sb_info *sbi,
					  const char *buf, size_t count)
{
	unsigned long t;

	if (parse_strtoul(buf, 0x40000000, &t))
		return -EINVAL;

	if (!is_power_of_2(t))
		return -EINVAL;

	sbi->s_inode_readahead_blks = t;
	return count;
}