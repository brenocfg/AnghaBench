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
struct scsi_device {int dummy; } ;
struct alua_dh_data {int* buff; int bufflen; unsigned char rel_port; unsigned char group_id; int /*<<< orphan*/  tpgs; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_DH_NAME ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int SCSI_DH_DEV_TEMP_BUSY ; 
 unsigned int SCSI_DH_DEV_UNSUPP ; 
 unsigned int SCSI_DH_OK ; 
 int /*<<< orphan*/  TPGS_MODE_NONE ; 
 int /*<<< orphan*/  TPGS_STATE_OPTIMIZED ; 
 scalar_t__ realloc_buffer (struct alua_dh_data*,int) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 
 unsigned int submit_vpd_inquiry (struct scsi_device*,struct alua_dh_data*) ; 

__attribute__((used)) static int alua_vpd_inquiry(struct scsi_device *sdev, struct alua_dh_data *h)
{
	int len;
	unsigned err;
	unsigned char *d;

 retry:
	err = submit_vpd_inquiry(sdev, h);

	if (err != SCSI_DH_OK)
		return err;

	/* Check if vpd page exceeds initial buffer */
	len = (h->buff[2] << 8) + h->buff[3] + 4;
	if (len > h->bufflen) {
		/* Resubmit with the correct length */
		if (realloc_buffer(h, len)) {
			sdev_printk(KERN_WARNING, sdev,
				    "%s: kmalloc buffer failed\n",
				    ALUA_DH_NAME);
			/* Temporary failure, bypass */
			return SCSI_DH_DEV_TEMP_BUSY;
		}
		goto retry;
	}

	/*
	 * Now look for the correct descriptor.
	 */
	d = h->buff + 4;
	while (d < h->buff + len) {
		switch (d[1] & 0xf) {
		case 0x4:
			/* Relative target port */
			h->rel_port = (d[6] << 8) + d[7];
			break;
		case 0x5:
			/* Target port group */
			h->group_id = (d[6] << 8) + d[7];
			break;
		default:
			break;
		}
		d += d[3] + 4;
	}

	if (h->group_id == -1) {
		/*
		 * Internal error; TPGS supported but required
		 * VPD identification descriptors not present.
		 * Disable ALUA support
		 */
		sdev_printk(KERN_INFO, sdev,
			    "%s: No target port descriptors found\n",
			    ALUA_DH_NAME);
		h->state = TPGS_STATE_OPTIMIZED;
		h->tpgs = TPGS_MODE_NONE;
		err = SCSI_DH_DEV_UNSUPP;
	} else {
		sdev_printk(KERN_INFO, sdev,
			    "%s: port group %02x rel port %02x\n",
			    ALUA_DH_NAME, h->group_id, h->rel_port);
	}

	return err;
}