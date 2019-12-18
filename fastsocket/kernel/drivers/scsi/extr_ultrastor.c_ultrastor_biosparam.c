#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {unsigned int heads; unsigned int sectors; } ;

/* Variables and functions */
 TYPE_1__ config ; 

int ultrastor_biosparam(struct scsi_device *sdev, struct block_device *bdev,
		sector_t capacity, int * dkinfo)
{
    int size = capacity;
    unsigned int s = config.heads * config.sectors;

    dkinfo[0] = config.heads;
    dkinfo[1] = config.sectors;
    dkinfo[2] = size / s;	/* Ignore partial cylinders */
#if 0
    if (dkinfo[2] > 1024)
	dkinfo[2] = 1024;
#endif
    return 0;
}