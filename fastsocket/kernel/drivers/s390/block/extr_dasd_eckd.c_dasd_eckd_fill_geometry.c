#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hd_geometry {int /*<<< orphan*/  heads; int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; } ;
struct TYPE_4__ {int /*<<< orphan*/  trk_per_cyl; int /*<<< orphan*/  no_cyl; } ;
struct dasd_eckd_private {TYPE_2__ rdc_data; } ;
struct dasd_block {int /*<<< orphan*/  bp_block; TYPE_1__* base; } ;
struct TYPE_3__ {scalar_t__ private; } ;

/* Variables and functions */
 scalar_t__ dasd_check_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recs_per_track (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dasd_eckd_fill_geometry(struct dasd_block *block, struct hd_geometry *geo)
{
	struct dasd_eckd_private *private;

	private = (struct dasd_eckd_private *) block->base->private;
	if (dasd_check_blocksize(block->bp_block) == 0) {
		geo->sectors = recs_per_track(&private->rdc_data,
					      0, block->bp_block);
	}
	geo->cylinders = private->rdc_data.no_cyl;
	geo->heads = private->rdc_data.trk_per_cyl;
	return 0;
}