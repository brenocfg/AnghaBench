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
struct ext4_xattr_entry {scalar_t__ e_value_block; int /*<<< orphan*/  e_value_offs; int /*<<< orphan*/  e_value_size; } ;

/* Variables and functions */
 int EIO ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ext4_xattr_check_entry(struct ext4_xattr_entry *entry, size_t size)
{
	size_t value_size = le32_to_cpu(entry->e_value_size);

	if (entry->e_value_block != 0 || value_size > size ||
	    le16_to_cpu(entry->e_value_offs) + value_size > size)
		return -EIO;
	return 0;
}