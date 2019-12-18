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
struct mca_device {int pos_id; int* pos; scalar_t__ slot; void* status; } ;

/* Variables and functions */
 void* MCA_ADAPTER_DISABLED ; 
 void* MCA_ADAPTER_ERROR ; 
 void* MCA_ADAPTER_NONE ; 
 void* MCA_ADAPTER_NORMAL ; 
 int MCA_ENABLED ; 
 scalar_t__ MCA_MAX_SLOT_NR ; 

__attribute__((used)) static void mca_configure_adapter_status(struct mca_device *mca_dev)
{
	mca_dev->status = MCA_ADAPTER_NONE;

	mca_dev->pos_id = mca_dev->pos[0]
		+ (mca_dev->pos[1] << 8);

	if (!mca_dev->pos_id && mca_dev->slot < MCA_MAX_SLOT_NR) {

		/*
		 * id = 0x0000 usually indicates hardware failure,
		 * however, ZP Gu (zpg@castle.net> reports that his 9556
		 * has 0x0000 as id and everything still works. There
		 * also seem to be an adapter with id = 0x0000; the
		 * NCR Parallel Bus Memory Card. Until this is confirmed,
		 * however, this code will stay.
		 */

		mca_dev->status = MCA_ADAPTER_ERROR;

		return;
	} else if (mca_dev->pos_id != 0xffff) {

		/*
		 * 0xffff usually indicates that there's no adapter,
		 * however, some integrated adapters may have 0xffff as
		 * their id and still be valid. Examples are on-board
		 * VGA of the 55sx, the integrated SCSI of the 56 & 57,
		 * and possibly also the 95 ULTIMEDIA.
		 */

		mca_dev->status = MCA_ADAPTER_NORMAL;
	}

	if ((mca_dev->pos_id == 0xffff ||
	    mca_dev->pos_id == 0x0000) && mca_dev->slot >= MCA_MAX_SLOT_NR) {
		int j;

		for (j = 2; j < 8; j++) {
			if (mca_dev->pos[j] != 0xff) {
				mca_dev->status = MCA_ADAPTER_NORMAL;
				break;
			}
		}
	}

	if (!(mca_dev->pos[2] & MCA_ENABLED)) {

		/* enabled bit is in POS 2 */

		mca_dev->status = MCA_ADAPTER_DISABLED;
	}
}