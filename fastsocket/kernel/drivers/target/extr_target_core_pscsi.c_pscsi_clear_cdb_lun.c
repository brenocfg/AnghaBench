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
#define  MAINTENANCE_IN 136 
#define  READ_10 135 
#define  READ_12 134 
#define  READ_16 133 
#define  SEND_DIAGNOSTIC 132 
#define  VERIFY 131 
#define  VERIFY_16 130 
#define  WRITE_VERIFY 129 
#define  WRITE_VERIFY_12 128 

__attribute__((used)) static inline void pscsi_clear_cdb_lun(unsigned char *cdb)
{
	switch (cdb[0]) {
	case READ_10: /* SBC - RDProtect */
	case READ_12: /* SBC - RDProtect */
	case READ_16: /* SBC - RDProtect */
	case SEND_DIAGNOSTIC: /* SPC - SELF-TEST Code */
	case VERIFY: /* SBC - VRProtect */
	case VERIFY_16: /* SBC - VRProtect */
	case WRITE_VERIFY: /* SBC - VRProtect */
	case WRITE_VERIFY_12: /* SBC - VRProtect */
	case MAINTENANCE_IN: /* SPC - Parameter Data Format for SA RTPG */
		break;
	default:
		cdb[1] &= 0x1f; /* clear logical unit number */
		break;
	}
}