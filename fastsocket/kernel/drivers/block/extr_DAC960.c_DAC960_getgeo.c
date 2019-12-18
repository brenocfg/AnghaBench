#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct hd_geometry {int heads; int sectors; int cylinders; } ;
struct gendisk {scalar_t__ private_data; TYPE_1__* queue; } ;
struct block_device {struct gendisk* bd_disk; } ;
struct TYPE_11__ {TYPE_5__** LogicalDeviceInformation; } ;
struct TYPE_10__ {int GeometryTranslationHeads; int GeometryTranslationSectors; TYPE_2__* LogicalDriveInformation; } ;
struct TYPE_13__ {scalar_t__ FirmwareType; TYPE_4__ V2; TYPE_3__ V1; } ;
struct TYPE_12__ {int DriveGeometry; int ConfigurableDeviceSize; } ;
struct TYPE_9__ {int LogicalDriveSize; } ;
struct TYPE_8__ {TYPE_6__* queuedata; } ;
typedef  TYPE_5__ DAC960_V2_LogicalDeviceInfo_T ;
typedef  TYPE_6__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_Error (char*,TYPE_6__*,int) ; 
 scalar_t__ DAC960_V1_Controller ; 
#define  DAC960_V2_Geometry_128_32 129 
#define  DAC960_V2_Geometry_255_63 128 
 int EINVAL ; 

__attribute__((used)) static int DAC960_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct gendisk *disk = bdev->bd_disk;
	DAC960_Controller_T *p = disk->queue->queuedata;
	int drive_nr = (long)disk->private_data;

	if (p->FirmwareType == DAC960_V1_Controller) {
		geo->heads = p->V1.GeometryTranslationHeads;
		geo->sectors = p->V1.GeometryTranslationSectors;
		geo->cylinders = p->V1.LogicalDriveInformation[drive_nr].
			LogicalDriveSize / (geo->heads * geo->sectors);
	} else {
		DAC960_V2_LogicalDeviceInfo_T *i =
			p->V2.LogicalDeviceInformation[drive_nr];
		switch (i->DriveGeometry) {
		case DAC960_V2_Geometry_128_32:
			geo->heads = 128;
			geo->sectors = 32;
			break;
		case DAC960_V2_Geometry_255_63:
			geo->heads = 255;
			geo->sectors = 63;
			break;
		default:
			DAC960_Error("Illegal Logical Device Geometry %d\n",
					p, i->DriveGeometry);
			return -EINVAL;
		}

		geo->cylinders = i->ConfigurableDeviceSize /
			(geo->heads * geo->sectors);
	}
	
	return 0;
}