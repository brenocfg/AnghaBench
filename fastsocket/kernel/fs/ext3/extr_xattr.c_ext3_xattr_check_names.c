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
struct ext3_xattr_entry {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 struct ext3_xattr_entry* EXT3_XATTR_NEXT (struct ext3_xattr_entry*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext3_xattr_entry*) ; 

__attribute__((used)) static int
ext3_xattr_check_names(struct ext3_xattr_entry *entry, void *end)
{
	while (!IS_LAST_ENTRY(entry)) {
		struct ext3_xattr_entry *next = EXT3_XATTR_NEXT(entry);
		if ((void *)next >= end)
			return -EIO;
		entry = next;
	}
	return 0;
}