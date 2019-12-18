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
struct TYPE_3__ {int blk_size; int /*<<< orphan*/  blk_bdsa; } ;
struct dasd_fba_private {TYPE_1__ rdc_data; } ;
struct dasd_block {int bp_block; scalar_t__ s2b_shift; int /*<<< orphan*/  blocks; TYPE_2__* base; } ;
struct TYPE_4__ {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int dasd_check_blocksize (int) ; 

__attribute__((used)) static int dasd_fba_do_analysis(struct dasd_block *block)
{
	struct dasd_fba_private *private;
	int sb, rc;

	private = (struct dasd_fba_private *) block->base->private;
	rc = dasd_check_blocksize(private->rdc_data.blk_size);
	if (rc) {
		DBF_DEV_EVENT(DBF_WARNING, block->base, "unknown blocksize %d",
			    private->rdc_data.blk_size);
		return rc;
	}
	block->blocks = private->rdc_data.blk_bdsa;
	block->bp_block = private->rdc_data.blk_size;
	block->s2b_shift = 0;	/* bits to shift 512 to get a block */
	for (sb = 512; sb < private->rdc_data.blk_size; sb = sb << 1)
		block->s2b_shift++;
	return 0;
}