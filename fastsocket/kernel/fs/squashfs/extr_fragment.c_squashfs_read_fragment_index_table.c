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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/ * ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SQUASHFS_FRAGMENT_INDEX_BYTES (unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int squashfs_read_table (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__le64 *squashfs_read_fragment_index_table(struct super_block *sb,
	u64 fragment_table_start, unsigned int fragments)
{
	unsigned int length = SQUASHFS_FRAGMENT_INDEX_BYTES(fragments);
	__le64 *fragment_index;
	int err;

	/* Allocate fragment lookup table indexes */
	fragment_index = kmalloc(length, GFP_KERNEL);
	if (fragment_index == NULL) {
		ERROR("Failed to allocate fragment index table\n");
		return ERR_PTR(-ENOMEM);
	}

	err = squashfs_read_table(sb, fragment_index, fragment_table_start,
			length);
	if (err < 0) {
		ERROR("unable to read fragment index table\n");
		kfree(fragment_index);
		return ERR_PTR(err);
	}

	return fragment_index;
}