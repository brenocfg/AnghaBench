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
struct scsi_sense_hdr {int sense_key; int asc; int ascq; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int ADD_TO_MLQUEUE ; 
#define  NOT_READY 129 
 int SCSI_RETURN_NOT_HANDLED ; 
 int SUCCESS ; 
#define  UNIT_ATTENTION 128 

__attribute__((used)) static int alua_check_sense(struct scsi_device *sdev,
			    struct scsi_sense_hdr *sense_hdr)
{
	switch (sense_hdr->sense_key) {
	case NOT_READY:
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x0a)
			/*
			 * LUN Not Accessible - ALUA state transition
			 */
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x0b)
			/*
			 * LUN Not Accessible -- Target port in standby state
			 */
			return SUCCESS;
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x0c)
			/*
			 * LUN Not Accessible -- Target port in unavailable state
			 */
			return SUCCESS;
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x12)
			/*
			 * LUN Not Ready -- Offline
			 */
			return SUCCESS;
		break;
	case UNIT_ATTENTION:
		if (sense_hdr->asc == 0x29 && sense_hdr->ascq == 0x00)
			/*
			 * Power On, Reset, or Bus Device Reset, just retry.
			 */
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0x2a && sense_hdr->ascq == 0x01)
			/*
			 * Mode Parameters Changed
			 */
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0x2a && sense_hdr->ascq == 0x06)
			/*
			 * ALUA state changed
			 */
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0x2a && sense_hdr->ascq == 0x07)
			/*
			 * Implicit ALUA state transition failed
			 */
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0x3f && sense_hdr->ascq == 0x03)
			/*
			 * Inquiry data has changed
			 */
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0x3f && sense_hdr->ascq == 0x0e)
			/*
			 * REPORTED_LUNS_DATA_HAS_CHANGED is reported
			 * when switching controllers on targets like
			 * Intel Multi-Flex. We can just retry.
			 */
			return ADD_TO_MLQUEUE;
		break;
	}

	return SCSI_RETURN_NOT_HANDLED;
}