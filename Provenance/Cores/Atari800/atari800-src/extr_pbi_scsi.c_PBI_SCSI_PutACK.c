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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PBI_SCSI_ACK ; 
 int /*<<< orphan*/  PBI_SCSI_REQ ; 
 scalar_t__ SCSI_PHASE_SELECTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scsi_nextbyte () ; 
 scalar_t__ scsi_phase ; 

void PBI_SCSI_PutACK(int newack)
{
	if (newack != PBI_SCSI_ACK) {
		/* ACK changed state */
		PBI_SCSI_ACK = newack;
		if (PBI_SCSI_ACK) {
			/* REQ goes false when ACK goes true */
			PBI_SCSI_REQ = FALSE;
		}
		else {
			/* falling ACK triggers next byte */
			if (scsi_phase != SCSI_PHASE_SELECTION) {
				PBI_SCSI_REQ = TRUE;
				scsi_nextbyte();
			}
		}
	}
}