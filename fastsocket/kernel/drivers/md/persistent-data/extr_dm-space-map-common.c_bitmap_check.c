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
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
struct disk_bitmap_header {scalar_t__ csum; int /*<<< orphan*/  not_used; int /*<<< orphan*/  blocknr; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_CSUM_XOR ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,scalar_t__,scalar_t__) ; 
 int EILSEQ ; 
 int ENOTBLK ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct disk_bitmap_header* dm_block_data (struct dm_block*) ; 
 scalar_t__ dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_checksum (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bitmap_check(struct dm_block_validator *v,
			struct dm_block *b,
			size_t block_size)
{
	struct disk_bitmap_header *disk_header = dm_block_data(b);
	__le32 csum_disk;

	if (dm_block_location(b) != le64_to_cpu(disk_header->blocknr)) {
		DMERR_LIMIT("bitmap check failed: blocknr %llu != wanted %llu",
			    le64_to_cpu(disk_header->blocknr), dm_block_location(b));
		return -ENOTBLK;
	}

	csum_disk = cpu_to_le32(dm_bm_checksum(&disk_header->not_used,
					       block_size - sizeof(__le32),
					       BITMAP_CSUM_XOR));
	if (csum_disk != disk_header->csum) {
		DMERR_LIMIT("bitmap check failed: csum %u != wanted %u",
			    le32_to_cpu(csum_disk), le32_to_cpu(disk_header->csum));
		return -EILSEQ;
	}

	return 0;
}