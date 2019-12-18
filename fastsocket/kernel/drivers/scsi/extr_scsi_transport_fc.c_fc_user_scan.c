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
typedef  scalar_t__ uint ;
struct Scsi_Host {scalar_t__ max_channel; scalar_t__ max_id; scalar_t__ max_lun; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SCAN_WILD_CARD ; 
 int /*<<< orphan*/  fc_user_scan_tgt (struct Scsi_Host*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
fc_user_scan(struct Scsi_Host *shost, uint channel, uint id, uint lun)
{
	uint chlo, chhi;
	uint tgtlo, tgthi;

	if (((channel != SCAN_WILD_CARD) && (channel > shost->max_channel)) ||
	    ((id != SCAN_WILD_CARD) && (id >= shost->max_id)) ||
	    ((lun != SCAN_WILD_CARD) && (lun > shost->max_lun)))
		return -EINVAL;

	if (channel == SCAN_WILD_CARD) {
		chlo = 0;
		chhi = shost->max_channel + 1;
	} else {
		chlo = channel;
		chhi = channel + 1;
	}

	if (id == SCAN_WILD_CARD) {
		tgtlo = 0;
		tgthi = shost->max_id;
	} else {
		tgtlo = id;
		tgthi = id + 1;
	}

	for ( ; chlo < chhi; chlo++)
		for ( ; tgtlo < tgthi; tgtlo++)
			fc_user_scan_tgt(shost, chlo, tgtlo, lun);

	return 0;
}