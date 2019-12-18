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
struct scsi_device {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  sector_div (int,int) ; 

__attribute__((used)) static int stex_biosparam(struct scsi_device *sdev,
	struct block_device *bdev, sector_t capacity, int geom[])
{
	int heads = 255, sectors = 63;

	if (capacity < 0x200000) {
		heads = 64;
		sectors = 32;
	}

	sector_div(capacity, heads * sectors);

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = capacity;

	return 0;
}