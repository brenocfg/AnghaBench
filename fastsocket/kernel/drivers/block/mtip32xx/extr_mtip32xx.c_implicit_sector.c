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
#define  ATA_CMD_CONF_OVERLAY 138 
#define  ATA_CMD_PMP_READ 137 
#define  ATA_CMD_PMP_WRITE 136 
#define  ATA_CMD_SEC_DISABLE_PASS 135 
#define  ATA_CMD_SEC_ERASE_PREP 134 
#define  ATA_CMD_SEC_ERASE_UNIT 133 
#define  ATA_CMD_SEC_FREEZE_LOCK 132 
#define  ATA_CMD_SEC_SET_PASS 131 
#define  ATA_CMD_SEC_UNLOCK 130 
#define  ATA_CMD_SET_MAX 129 
#define  ATA_CMD_SMART 128 
 unsigned char ATA_DCO_IDENTIFY ; 
 unsigned char ATA_DCO_SET ; 
 unsigned char ATA_SET_MAX_UNLOCK ; 
 unsigned char ATA_SMART_READ_THRESHOLDS ; 
 unsigned char ATA_SMART_READ_VALUES ; 

__attribute__((used)) static unsigned int implicit_sector(unsigned char command,
				    unsigned char features)
{
	unsigned int rv = 0;

	/* list of commands that have an implicit sector count of 1 */
	switch (command) {
	case ATA_CMD_SEC_SET_PASS:
	case ATA_CMD_SEC_UNLOCK:
	case ATA_CMD_SEC_ERASE_PREP:
	case ATA_CMD_SEC_ERASE_UNIT:
	case ATA_CMD_SEC_FREEZE_LOCK:
	case ATA_CMD_SEC_DISABLE_PASS:
	case ATA_CMD_PMP_READ:
	case ATA_CMD_PMP_WRITE:
		rv = 1;
		break;
	case ATA_CMD_SET_MAX:
		if (features == ATA_SET_MAX_UNLOCK)
			rv = 1;
		break;
	case ATA_CMD_SMART:
		if ((features == ATA_SMART_READ_VALUES) ||
				(features == ATA_SMART_READ_THRESHOLDS))
			rv = 1;
		break;
	case ATA_CMD_CONF_OVERLAY:
		if ((features == ATA_DCO_IDENTIFY) ||
				(features == ATA_DCO_SET))
			rv = 1;
		break;
	}
	return rv;
}