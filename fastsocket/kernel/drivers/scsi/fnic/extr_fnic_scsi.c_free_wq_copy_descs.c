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
struct TYPE_2__ {int desc_count; int /*<<< orphan*/  desc_avail; } ;
struct vnic_wq_copy {int to_clean_index; TYPE_1__ ring; } ;
struct fnic {int* fw_ack_index; scalar_t__* fw_ack_recd; } ;

/* Variables and functions */

__attribute__((used)) static int free_wq_copy_descs(struct fnic *fnic, struct vnic_wq_copy *wq)
{
	/* if no Ack received from firmware, then nothing to clean */
	if (!fnic->fw_ack_recd[0])
		return 1;

	/*
	 * Update desc_available count based on number of freed descriptors
	 * Account for wraparound
	 */
	if (wq->to_clean_index <= fnic->fw_ack_index[0])
		wq->ring.desc_avail += (fnic->fw_ack_index[0]
					- wq->to_clean_index + 1);
	else
		wq->ring.desc_avail += (wq->ring.desc_count
					- wq->to_clean_index
					+ fnic->fw_ack_index[0] + 1);

	/*
	 * just bump clean index to ack_index+1 accounting for wraparound
	 * this will essentially free up all descriptors between
	 * to_clean_index and fw_ack_index, both inclusive
	 */
	wq->to_clean_index =
		(fnic->fw_ack_index[0] + 1) % wq->ring.desc_count;

	/* we have processed the acks received so far */
	fnic->fw_ack_recd[0] = 0;
	return 0;
}