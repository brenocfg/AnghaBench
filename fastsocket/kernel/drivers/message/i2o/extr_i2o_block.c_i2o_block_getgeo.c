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
struct hd_geometry {int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; int /*<<< orphan*/  cylinders; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2o_block_biosparam (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2o_block_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	i2o_block_biosparam(get_capacity(bdev->bd_disk),
			    &geo->cylinders, &geo->heads, &geo->sectors);
	return 0;
}