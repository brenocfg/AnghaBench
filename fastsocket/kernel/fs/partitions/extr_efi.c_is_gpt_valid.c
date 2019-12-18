#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct block_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  partition_entry_array_crc32; int /*<<< orphan*/  sizeof_partition_entry; int /*<<< orphan*/  num_partition_entries; int /*<<< orphan*/  last_usable_lba; int /*<<< orphan*/  first_usable_lba; int /*<<< orphan*/  my_lba; int /*<<< orphan*/  header_crc32; int /*<<< orphan*/  header_size; int /*<<< orphan*/  signature; } ;
typedef  TYPE_1__ gpt_header ;
typedef  TYPE_1__ gpt_entry ;

/* Variables and functions */
 scalar_t__ GPT_HEADER_SIGNATURE ; 
 TYPE_1__* alloc_read_gpt_entries (struct block_device*,TYPE_1__*) ; 
 TYPE_1__* alloc_read_gpt_header (struct block_device*,scalar_t__) ; 
 int bdev_logical_block_size (struct block_device*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int efi_crc32 (unsigned char const*,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 scalar_t__ last_lba (struct block_device*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int
is_gpt_valid(struct block_device *bdev, u64 lba,
	     gpt_header **gpt, gpt_entry **ptes)
{
	u32 crc, origcrc;
	u64 lastlba;

	if (!bdev || !gpt || !ptes)
		return 0;
	if (!(*gpt = alloc_read_gpt_header(bdev, lba)))
		return 0;

	/* Check the GUID Partition Table signature */
	if (le64_to_cpu((*gpt)->signature) != GPT_HEADER_SIGNATURE) {
		pr_debug("GUID Partition Table Header signature is wrong:"
			 "%lld != %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->signature),
			 (unsigned long long)GPT_HEADER_SIGNATURE);
		goto fail;
	}

	/* Check the GUID Partition Table header size */
	if (le32_to_cpu((*gpt)->header_size) >
			bdev_logical_block_size(bdev)) {
		pr_debug("GUID Partition Table Header size is wrong: %u > %u\n",
			le32_to_cpu((*gpt)->header_size),
			bdev_logical_block_size(bdev));
		goto fail;
	}

	/* Check the GUID Partition Table CRC */
	origcrc = le32_to_cpu((*gpt)->header_crc32);
	(*gpt)->header_crc32 = 0;
	crc = efi_crc32((const unsigned char *) (*gpt), le32_to_cpu((*gpt)->header_size));

	if (crc != origcrc) {
		pr_debug("GUID Partition Table Header CRC is wrong: %x != %x\n",
			 crc, origcrc);
		goto fail;
	}
	(*gpt)->header_crc32 = cpu_to_le32(origcrc);

	/* Check that the my_lba entry points to the LBA that contains
	 * the GUID Partition Table */
	if (le64_to_cpu((*gpt)->my_lba) != lba) {
		pr_debug("GPT my_lba incorrect: %lld != %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->my_lba),
			 (unsigned long long)lba);
		goto fail;
	}

	/* Check the first_usable_lba and last_usable_lba are
	 * within the disk.
	 */
	lastlba = last_lba(bdev);
	if (le64_to_cpu((*gpt)->first_usable_lba) > lastlba) {
		pr_debug("GPT: first_usable_lba incorrect: %lld > %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->first_usable_lba),
			 (unsigned long long)lastlba);
		goto fail;
	}
	if (le64_to_cpu((*gpt)->last_usable_lba) > lastlba) {
		pr_debug("GPT: last_usable_lba incorrect: %lld > %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->last_usable_lba),
			 (unsigned long long)lastlba);
		goto fail;
	}

	/* Check that sizeof_partition_entry has the correct value */
	if (le32_to_cpu((*gpt)->sizeof_partition_entry) != sizeof(gpt_entry)) {
			pr_debug("GUID Partitition Entry Size check failed.\n");
			goto fail;
	}

	if (!(*ptes = alloc_read_gpt_entries(bdev, *gpt)))
		goto fail;

	/* Check the GUID Partition Entry Array CRC */
	crc = efi_crc32((const unsigned char *) (*ptes),
			le32_to_cpu((*gpt)->num_partition_entries) *
			le32_to_cpu((*gpt)->sizeof_partition_entry));

	if (crc != le32_to_cpu((*gpt)->partition_entry_array_crc32)) {
		pr_debug("GUID Partitition Entry Array CRC check failed.\n");
		goto fail_ptes;
	}

	/* We're done, all's well */
	return 1;

 fail_ptes:
	kfree(*ptes);
	*ptes = NULL;
 fail:
	kfree(*gpt);
	*gpt = NULL;
	return 0;
}