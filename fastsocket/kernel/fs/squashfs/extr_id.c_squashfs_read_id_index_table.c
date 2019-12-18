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
 unsigned int SQUASHFS_ID_BLOCK_BYTES (unsigned short) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int squashfs_read_table (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__le64 *squashfs_read_id_index_table(struct super_block *sb,
			u64 id_table_start, unsigned short no_ids)
{
	unsigned int length = SQUASHFS_ID_BLOCK_BYTES(no_ids);
	__le64 *id_table;
	int err;

	TRACE("In read_id_index_table, length %d\n", length);

	/* Allocate id lookup table indexes */
	id_table = kmalloc(length, GFP_KERNEL);
	if (id_table == NULL) {
		ERROR("Failed to allocate id index table\n");
		return ERR_PTR(-ENOMEM);
	}

	err = squashfs_read_table(sb, id_table, id_table_start, length);
	if (err < 0) {
		ERROR("unable to read id index table\n");
		kfree(id_table);
		return ERR_PTR(err);
	}

	return id_table;
}