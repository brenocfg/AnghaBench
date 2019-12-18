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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  THIN_METADATA_BLOCK_SIZE ; 
 int /*<<< orphan*/  get_metadata_dev_size (struct block_device*) ; 
 int /*<<< orphan*/  sector_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dm_block_t get_metadata_dev_size_in_blocks(struct block_device *bdev)
{
	sector_t metadata_dev_size = get_metadata_dev_size(bdev);

	sector_div(metadata_dev_size, THIN_METADATA_BLOCK_SIZE);

	return metadata_dev_size;
}