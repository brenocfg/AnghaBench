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
typedef  int u64 ;
struct rsxx_cardinfo {int size8; } ;
struct hd_geometry {int heads; int sectors; int cylinders; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {struct rsxx_cardinfo* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static int rsxx_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct rsxx_cardinfo *card = bdev->bd_disk->private_data;
	u64 blocks = card->size8 >> 9;

	/*
	 * get geometry: Fake it. I haven't found any drivers that set
	 * geo->start, so we won't either.
	 */
	if (card->size8) {
		geo->heads = 64;
		geo->sectors = 16;
		do_div(blocks, (geo->heads * geo->sectors));
		geo->cylinders = blocks;
	} else {
		geo->heads = 0;
		geo->sectors = 0;
		geo->cylinders = 0;
	}
	return 0;
}