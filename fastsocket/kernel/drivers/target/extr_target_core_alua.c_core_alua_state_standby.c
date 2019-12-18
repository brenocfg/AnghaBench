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
typedef  int /*<<< orphan*/  u8 ;
struct se_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCQ_04H_ALUA_TG_PT_STANDBY ; 
#define  INQUIRY 144 
#define  LOG_SELECT 143 
#define  LOG_SENSE 142 
#define  MAINTENANCE_IN 141 
#define  MAINTENANCE_OUT 140 
#define  MI_REPORT_TARGET_PGS 139 
#define  MODE_SELECT 138 
#define  MODE_SENSE 137 
#define  MO_SET_TARGET_PGS 136 
#define  PERSISTENT_RESERVE_IN 135 
#define  PERSISTENT_RESERVE_OUT 134 
#define  READ_BUFFER 133 
#define  RECEIVE_DIAGNOSTIC 132 
#define  REPORT_LUNS 131 
#define  REQUEST_SENSE 130 
#define  SEND_DIAGNOSTIC 129 
#define  WRITE_BUFFER 128 

__attribute__((used)) static inline int core_alua_state_standby(
	struct se_cmd *cmd,
	unsigned char *cdb,
	u8 *alua_ascq)
{
	/*
	 * Allowed CDBs for ALUA_ACCESS_STATE_STANDBY as defined by
	 * spc4r17 section 5.9.2.4.4
	 */
	switch (cdb[0]) {
	case INQUIRY:
	case LOG_SELECT:
	case LOG_SENSE:
	case MODE_SELECT:
	case MODE_SENSE:
	case REPORT_LUNS:
	case RECEIVE_DIAGNOSTIC:
	case SEND_DIAGNOSTIC:
		return 0;
	case MAINTENANCE_IN:
		switch (cdb[1] & 0x1f) {
		case MI_REPORT_TARGET_PGS:
			return 0;
		default:
			*alua_ascq = ASCQ_04H_ALUA_TG_PT_STANDBY;
			return 1;
		}
	case MAINTENANCE_OUT:
		switch (cdb[1]) {
		case MO_SET_TARGET_PGS:
			return 0;
		default:
			*alua_ascq = ASCQ_04H_ALUA_TG_PT_STANDBY;
			return 1;
		}
	case REQUEST_SENSE:
	case PERSISTENT_RESERVE_IN:
	case PERSISTENT_RESERVE_OUT:
	case READ_BUFFER:
	case WRITE_BUFFER:
		return 0;
	default:
		*alua_ascq = ASCQ_04H_ALUA_TG_PT_STANDBY;
		return 1;
	}

	return 0;
}