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
struct hd_geometry {unsigned long cylinders; int heads; int sectors; int start; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int xpram_pages ; 

__attribute__((used)) static int xpram_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	unsigned long size;

	/*
	 * get geometry: we have to fake one...  trim the size to a
	 * multiple of 64 (32k): tell we have 16 sectors, 4 heads,
	 * whatever cylinders. Tell also that data starts at sector. 4.
	 */
	size = (xpram_pages * 8) & ~0x3f;
	geo->cylinders = size >> 6;
	geo->heads = 4;
	geo->sectors = 16;
	geo->start = 4;
	return 0;
}