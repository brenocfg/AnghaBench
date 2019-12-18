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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct block_device {int dummy; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int bdev_logical_block_size (struct block_device*) ; 
 int last_lba (struct block_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 unsigned char* read_dev_sector (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
read_lba(struct block_device *bdev, u64 lba, u8 * buffer, size_t count)
{
	size_t totalreadcount = 0;
	sector_t n = lba * (bdev_logical_block_size(bdev) / 512);

	if (!bdev || !buffer || lba > last_lba(bdev))
                return 0;

	while (count) {
		int copied = 512;
		Sector sect;
		unsigned char *data = read_dev_sector(bdev, n++, &sect);
		if (!data)
			break;
		if (copied > count)
			copied = count;
		memcpy(buffer, data, copied);
		put_dev_sector(sect);
		buffer += copied;
		totalreadcount +=copied;
		count -= copied;
	}
	return totalreadcount;
}