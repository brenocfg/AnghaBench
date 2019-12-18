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
struct ext4_xattr_entry {int /*<<< orphan*/  e_value_offs; scalar_t__ e_value_size; int /*<<< orphan*/  e_value_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 

__attribute__((used)) static void ext4_xattr_shift_entries(struct ext4_xattr_entry *entry,
				     int value_offs_shift, void *to,
				     void *from, size_t n, int blocksize)
{
	struct ext4_xattr_entry *last = entry;
	int new_offs;

	/* Adjust the value offsets of the entries */
	for (; !IS_LAST_ENTRY(last); last = EXT4_XATTR_NEXT(last)) {
		if (!last->e_value_block && last->e_value_size) {
			new_offs = le16_to_cpu(last->e_value_offs) +
							value_offs_shift;
			BUG_ON(new_offs + le32_to_cpu(last->e_value_size)
				 > blocksize);
			last->e_value_offs = cpu_to_le16(new_offs);
		}
	}
	/* Shift the entries by n bytes */
	memmove(to, from, n);
}