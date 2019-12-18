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
typedef  unsigned int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  driver_name ; 
 scalar_t__ ext_tran ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ scsicam_bios_param (struct block_device*,unsigned int,int*) ; 

int eata2x_bios_param(struct scsi_device *sdev, struct block_device *bdev,
		      sector_t capacity, int *dkinfo)
{
	unsigned int size = capacity;

	if (ext_tran || (scsicam_bios_param(bdev, capacity, dkinfo) < 0)) {
		dkinfo[0] = 255;
		dkinfo[1] = 63;
		dkinfo[2] = size / (dkinfo[0] * dkinfo[1]);
	}
#if defined (DEBUG_GEOMETRY)
	printk("%s: bios_param, head=%d, sec=%d, cyl=%d.\n", driver_name,
	       dkinfo[0], dkinfo[1], dkinfo[2]);
#endif

	return 0;
}