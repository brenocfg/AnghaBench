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
#define  MAINTENANCE_IN 134 
#define  MAINTENANCE_OUT 133 
#define  SERVICE_ACTION_IN_12 132 
#define  SERVICE_ACTION_IN_16 131 
#define  SERVICE_ACTION_OUT_12 130 
#define  SERVICE_ACTION_OUT_16 129 
#define  VARIABLE_LENGTH_CMD 128 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int scsi_varlen_cdb_length (unsigned char*) ; 

__attribute__((used)) static void print_opcode_name(unsigned char * cdbp, int cdb_len)
{
	int sa, len, cdb0;

	cdb0 = cdbp[0];
	switch(cdb0) {
	case VARIABLE_LENGTH_CMD:
		len = scsi_varlen_cdb_length(cdbp);
		if (len < 10) {
			printk("short opcode=0x%x command, len=%d "
			       "ext_len=%d", cdb0, len, cdb_len);
			break;
		}
		sa = (cdbp[8] << 8) + cdbp[9];
		printk("cdb[0]=0x%x, sa=0x%x", cdb0, sa);
		if (len != cdb_len)
			printk(", in_cdb_len=%d, ext_len=%d", len, cdb_len);
		break;
	case MAINTENANCE_IN:
	case MAINTENANCE_OUT:
	case SERVICE_ACTION_IN_12:
	case SERVICE_ACTION_OUT_12:
	case SERVICE_ACTION_IN_16:
	case SERVICE_ACTION_OUT_16:
		sa = cdbp[1] & 0x1f;
		printk("cdb[0]=0x%x, sa=0x%x", cdb0, sa);
		break;
	default:
		if (cdb0 < 0xc0)
			printk("cdb[0]=0x%x", cdb0);
		else
			printk("cdb[0]=0x%x (vendor)", cdb0);
		break;
	}
}