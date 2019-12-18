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
struct ext4_xattr_entry {int /*<<< orphan*/  e_value_offs; scalar_t__ e_value_size; int /*<<< orphan*/  e_value_block; int /*<<< orphan*/  e_name_len; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ EXT4_XATTR_LEN (int /*<<< orphan*/ ) ; 
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ext4_xattr_free_space(struct ext4_xattr_entry *last,
				    size_t *min_offs, void *base, int *total)
{
	for (; !IS_LAST_ENTRY(last); last = EXT4_XATTR_NEXT(last)) {
		*total += EXT4_XATTR_LEN(last->e_name_len);
		if (!last->e_value_block && last->e_value_size) {
			size_t offs = le16_to_cpu(last->e_value_offs);
			if (offs < *min_offs)
				*min_offs = offs;
		}
	}
	return (*min_offs - ((void *)last - base) - sizeof(__u32));
}