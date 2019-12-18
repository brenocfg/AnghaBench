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
struct scsi_device {int type; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int sector_div (int,int) ; 

__attribute__((used)) static int adpt_bios_param(struct scsi_device *sdev, struct block_device *dev,
		sector_t capacity, int geom[])
{
	int heads=-1;
	int sectors=-1;
	int cylinders=-1;

	// *** First lets set the default geometry ****
	
	// If the capacity is less than ox2000
	if (capacity < 0x2000 ) {	// floppy
		heads = 18;
		sectors = 2;
	} 
	// else if between 0x2000 and 0x20000
	else if (capacity < 0x20000) {
		heads = 64;
		sectors = 32;
	}
	// else if between 0x20000 and 0x40000
	else if (capacity < 0x40000) {
		heads = 65;
		sectors = 63;
	}
	// else if between 0x4000 and 0x80000
	else if (capacity < 0x80000) {
		heads = 128;
		sectors = 63;
	}
	// else if greater than 0x80000
	else {
		heads = 255;
		sectors = 63;
	}
	cylinders = sector_div(capacity, heads * sectors);

	// Special case if CDROM
	if(sdev->type == 5) {  // CDROM
		heads = 252;
		sectors = 63;
		cylinders = 1111;
	}

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;
	
	PDEBUG("adpt_bios_param: exit\n");
	return 0;
}