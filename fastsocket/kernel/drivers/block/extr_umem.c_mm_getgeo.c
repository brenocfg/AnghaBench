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
struct hd_geometry {int heads; int sectors; int cylinders; } ;
struct cardinfo {int mm_size; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {struct cardinfo* private_data; } ;

/* Variables and functions */
 int MM_HARDSECT ; 

__attribute__((used)) static int mm_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct cardinfo *card = bdev->bd_disk->private_data;
	int size = card->mm_size * (1024 / MM_HARDSECT);

	/*
	 * get geometry: we have to fake one...  trim the size to a
	 * multiple of 2048 (1M): tell we have 32 sectors, 64 heads,
	 * whatever cylinders.
	 */
	geo->heads     = 64;
	geo->sectors   = 32;
	geo->cylinders = size / (geo->heads * geo->sectors);
	return 0;
}