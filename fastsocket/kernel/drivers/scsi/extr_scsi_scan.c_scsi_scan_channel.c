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
typedef  unsigned int uint ;
struct Scsi_Host {unsigned int max_id; int /*<<< orphan*/  shost_gendev; scalar_t__ reverse_ordering; } ;

/* Variables and functions */
 unsigned int SCAN_WILD_CARD ; 
 int /*<<< orphan*/  __scsi_scan_target (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void scsi_scan_channel(struct Scsi_Host *shost, unsigned int channel,
			      unsigned int id, unsigned int lun, int rescan)
{
	uint order_id;

	if (id == SCAN_WILD_CARD)
		for (id = 0; id < shost->max_id; ++id) {
			/*
			 * XXX adapter drivers when possible (FCP, iSCSI)
			 * could modify max_id to match the current max,
			 * not the absolute max.
			 *
			 * XXX add a shost id iterator, so for example,
			 * the FC ID can be the same as a target id
			 * without a huge overhead of sparse id's.
			 */
			if (shost->reverse_ordering)
				/*
				 * Scan from high to low id.
				 */
				order_id = shost->max_id - id - 1;
			else
				order_id = id;
			__scsi_scan_target(&shost->shost_gendev, channel,
					order_id, lun, rescan);
		}
	else
		__scsi_scan_target(&shost->shost_gendev, channel,
				id, lun, rescan);
}