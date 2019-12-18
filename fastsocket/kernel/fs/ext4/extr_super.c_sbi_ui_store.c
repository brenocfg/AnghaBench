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
struct ext4_sb_info {int dummy; } ;
struct ext4_attr {int offset; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ parse_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t sbi_ui_store(struct ext4_attr *a,
			    struct ext4_sb_info *sbi,
			    const char *buf, size_t count)
{
	unsigned int *ui = (unsigned int *) (((char *) sbi) + a->offset);
	unsigned long t;

	if (parse_strtoul(buf, 0xffffffff, &t))
		return -EINVAL;
	*ui = t;
	return count;
}