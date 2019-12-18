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

__attribute__((used)) static int i2o_scsi_bios_param(struct scsi_device *sdev,
			       struct block_device *dev, sector_t capacity,
			       int *ip)
{
	int size;

	size = capacity;
	ip[0] = 64;		/* heads                        */
	ip[1] = 32;		/* sectors                      */
	if ((ip[2] = size >> 11) > 1024) {	/* cylinders, test for big disk */
		ip[0] = 255;	/* heads                        */
		ip[1] = 63;	/* sectors                      */
		ip[2] = size / (255 * 63);	/* cylinders                    */
	}
	return 0;
}