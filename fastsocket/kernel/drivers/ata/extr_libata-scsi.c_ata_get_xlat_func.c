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
typedef  int u8 ;
struct ata_device {int dummy; } ;
typedef  int /*<<< orphan*/ * ata_xlat_func_t ;

/* Variables and functions */
#define  ATA_12 139 
#define  ATA_16 138 
#define  READ_10 137 
#define  READ_16 136 
#define  READ_6 135 
#define  START_STOP 134 
#define  SYNCHRONIZE_CACHE 133 
#define  VERIFY 132 
#define  VERIFY_16 131 
#define  WRITE_10 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 int /*<<< orphan*/ * ata_scsi_flush_xlat ; 
 int /*<<< orphan*/ * ata_scsi_pass_thru ; 
 int /*<<< orphan*/ * ata_scsi_rw_xlat ; 
 int /*<<< orphan*/ * ata_scsi_start_stop_xlat ; 
 int /*<<< orphan*/ * ata_scsi_verify_xlat ; 
 int /*<<< orphan*/ * ata_scsi_write_same_xlat ; 
 int /*<<< orphan*/  ata_try_flush_cache (struct ata_device*) ; 

__attribute__((used)) static inline ata_xlat_func_t ata_get_xlat_func(struct ata_device *dev, u8 cmd)
{
	switch (cmd) {
	case READ_6:
	case READ_10:
	case READ_16:

	case WRITE_6:
	case WRITE_10:
	case WRITE_16:
		return ata_scsi_rw_xlat;

	case 0x93 /*WRITE_SAME_16*/:
		return ata_scsi_write_same_xlat;

	case SYNCHRONIZE_CACHE:
		if (ata_try_flush_cache(dev))
			return ata_scsi_flush_xlat;
		break;

	case VERIFY:
	case VERIFY_16:
		return ata_scsi_verify_xlat;

	case ATA_12:
	case ATA_16:
		return ata_scsi_pass_thru;

	case START_STOP:
		return ata_scsi_start_stop_xlat;
	}

	return NULL;
}