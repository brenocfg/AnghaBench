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
struct ext2_xattr_header {int dummy; } ;
struct ext2_xattr_entry {scalar_t__ e_hash; scalar_t__ e_name_index; scalar_t__ e_name_len; scalar_t__ e_value_size; char* e_name; scalar_t__ e_value_block; int /*<<< orphan*/  e_value_offs; } ;

/* Variables and functions */
 int EIO ; 
 struct ext2_xattr_entry* ENTRY (struct ext2_xattr_header*) ; 
 struct ext2_xattr_entry* EXT2_XATTR_NEXT (struct ext2_xattr_entry*) ; 
 scalar_t__ IS_LAST_ENTRY (struct ext2_xattr_entry*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 

__attribute__((used)) static int
ext2_xattr_cmp(struct ext2_xattr_header *header1,
	       struct ext2_xattr_header *header2)
{
	struct ext2_xattr_entry *entry1, *entry2;

	entry1 = ENTRY(header1+1);
	entry2 = ENTRY(header2+1);
	while (!IS_LAST_ENTRY(entry1)) {
		if (IS_LAST_ENTRY(entry2))
			return 1;
		if (entry1->e_hash != entry2->e_hash ||
		    entry1->e_name_index != entry2->e_name_index ||
		    entry1->e_name_len != entry2->e_name_len ||
		    entry1->e_value_size != entry2->e_value_size ||
		    memcmp(entry1->e_name, entry2->e_name, entry1->e_name_len))
			return 1;
		if (entry1->e_value_block != 0 || entry2->e_value_block != 0)
			return -EIO;
		if (memcmp((char *)header1 + le16_to_cpu(entry1->e_value_offs),
			   (char *)header2 + le16_to_cpu(entry2->e_value_offs),
			   le32_to_cpu(entry1->e_value_size)))
			return 1;

		entry1 = EXT2_XATTR_NEXT(entry1);
		entry2 = EXT2_XATTR_NEXT(entry2);
	}
	if (!IS_LAST_ENTRY(entry2))
		return 1;
	return 0;
}