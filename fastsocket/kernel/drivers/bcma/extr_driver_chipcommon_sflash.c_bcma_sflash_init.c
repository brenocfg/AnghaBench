#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bcma_sflash_tbl_e {int id; int blocksize; int numblocks; int /*<<< orphan*/  name; } ;
struct bcma_sflash {int blocksize; int numblocks; int size; int present; int /*<<< orphan*/  window; } ;
struct bcma_drv_cc {int capabilities; struct bcma_sflash sflash; TYPE_1__* core; } ;
struct bcma_bus {int dummy; } ;
struct TYPE_7__ {struct bcma_sflash* platform_data; } ;
struct TYPE_8__ {TYPE_3__ dev; TYPE_2__* resource; } ;
struct TYPE_6__ {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_5__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int BCMA_CC_CAP_FLASHT ; 
 int /*<<< orphan*/  BCMA_CC_FLASHADDR ; 
 int /*<<< orphan*/  BCMA_CC_FLASHCTL_AT_STATUS ; 
 int /*<<< orphan*/  BCMA_CC_FLASHCTL_ST_DP ; 
 int /*<<< orphan*/  BCMA_CC_FLASHCTL_ST_RES ; 
 int /*<<< orphan*/  BCMA_CC_FLASHDATA ; 
#define  BCMA_CC_FLASHT_ATSER 129 
#define  BCMA_CC_FLASHT_STSER 128 
 int /*<<< orphan*/  BCMA_SOC_FLASH2 ; 
 int ENOTSUPP ; 
 int bcma_cc_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_cc_write32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*,...) ; 
 int /*<<< orphan*/  bcma_info (struct bcma_bus*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 struct bcma_sflash_tbl_e* bcma_sflash_at_tbl ; 
 int /*<<< orphan*/  bcma_sflash_cmd (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 TYPE_4__ bcma_sflash_dev ; 
 struct bcma_sflash_tbl_e* bcma_sflash_sst_tbl ; 
 struct bcma_sflash_tbl_e* bcma_sflash_st_tbl ; 

int bcma_sflash_init(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;
	struct bcma_sflash *sflash = &cc->sflash;
	struct bcma_sflash_tbl_e *e;
	u32 id, id2;

	switch (cc->capabilities & BCMA_CC_CAP_FLASHT) {
	case BCMA_CC_FLASHT_STSER:
		bcma_sflash_cmd(cc, BCMA_CC_FLASHCTL_ST_DP);

		bcma_cc_write32(cc, BCMA_CC_FLASHADDR, 0);
		bcma_sflash_cmd(cc, BCMA_CC_FLASHCTL_ST_RES);
		id = bcma_cc_read32(cc, BCMA_CC_FLASHDATA);

		bcma_cc_write32(cc, BCMA_CC_FLASHADDR, 1);
		bcma_sflash_cmd(cc, BCMA_CC_FLASHCTL_ST_RES);
		id2 = bcma_cc_read32(cc, BCMA_CC_FLASHDATA);

		switch (id) {
		case 0xbf:
			for (e = bcma_sflash_sst_tbl; e->name; e++) {
				if (e->id == id2)
					break;
			}
			break;
		case 0x13:
			return -ENOTSUPP;
		default:
			for (e = bcma_sflash_st_tbl; e->name; e++) {
				if (e->id == id)
					break;
			}
			break;
		}
		if (!e->name) {
			bcma_err(bus, "Unsupported ST serial flash (id: 0x%X, id2: 0x%X)\n", id, id2);
			return -ENOTSUPP;
		}

		break;
	case BCMA_CC_FLASHT_ATSER:
		bcma_sflash_cmd(cc, BCMA_CC_FLASHCTL_AT_STATUS);
		id = bcma_cc_read32(cc, BCMA_CC_FLASHDATA) & 0x3c;

		for (e = bcma_sflash_at_tbl; e->name; e++) {
			if (e->id == id)
				break;
		}
		if (!e->name) {
			bcma_err(bus, "Unsupported Atmel serial flash (id: 0x%X)\n", id);
			return -ENOTSUPP;
		}

		break;
	default:
		bcma_err(bus, "Unsupported flash type\n");
		return -ENOTSUPP;
	}

	sflash->window = BCMA_SOC_FLASH2;
	sflash->blocksize = e->blocksize;
	sflash->numblocks = e->numblocks;
	sflash->size = sflash->blocksize * sflash->numblocks;
	sflash->present = true;

	bcma_info(bus, "Found %s serial flash (size: %dKiB, blocksize: 0x%X, blocks: %d)\n",
		  e->name, sflash->size / 1024, sflash->blocksize,
		  sflash->numblocks);

	/* Prepare platform device, but don't register it yet. It's too early,
	 * malloc (required by device_private_init) is not available yet. */
	bcma_sflash_dev.resource[0].end = bcma_sflash_dev.resource[0].start +
					  sflash->size;
	bcma_sflash_dev.dev.platform_data = sflash;

	return 0;
}