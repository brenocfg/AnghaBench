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
 int /*<<< orphan*/  sector_div (int,unsigned long) ; 

__attribute__((used)) static int
megasas_bios_param(struct scsi_device *sdev, struct block_device *bdev,
		 sector_t capacity, int geom[])
{
	int heads;
	int sectors;
	sector_t cylinders;
	unsigned long tmp;
	/* Default heads (64) & sectors (32) */
	heads = 64;
	sectors = 32;

	tmp = heads * sectors;
	cylinders = capacity;

	sector_div(cylinders, tmp);

	/*
	 * Handle extended translation size for logical drives > 1Gb
	 */

	if (capacity >= 0x200000) {
		heads = 255;
		sectors = 63;
		tmp = heads*sectors;
		cylinders = capacity;
		sector_div(cylinders, tmp);
	}

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	return 0;
}