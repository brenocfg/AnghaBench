#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct pmcraid_resource_entry {int /*<<< orphan*/  cfg_entry; } ;
struct TYPE_9__ {scalar_t__ failing_lba_hi; scalar_t__ failing_lba_lo; } ;
struct TYPE_10__ {TYPE_4__ vset; } ;
struct pmcraid_ioasa {scalar_t__ ioasc; TYPE_5__ u; } ;
struct pmcraid_cmd {TYPE_3__* scsi_cmd; TYPE_2__* ioa_cb; } ;
struct TYPE_8__ {int* sense_buffer; int /*<<< orphan*/  result; TYPE_1__* device; } ;
struct TYPE_7__ {struct pmcraid_ioasa ioasa; } ;
struct TYPE_6__ {struct pmcraid_resource_entry* hostdata; } ;

/* Variables and functions */
 scalar_t__ PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC ; 
 int PMCRAID_IOASC_SENSE_CODE (scalar_t__) ; 
 int PMCRAID_IOASC_SENSE_KEY (scalar_t__) ; 
 int PMCRAID_IOASC_SENSE_QUAL (scalar_t__) ; 
 scalar_t__ RES_IS_VSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_frame_auto_sense(struct pmcraid_cmd *cmd)
{
	u8 *sense_buf = cmd->scsi_cmd->sense_buffer;
	struct pmcraid_resource_entry *res = cmd->scsi_cmd->device->hostdata;
	struct pmcraid_ioasa *ioasa = &cmd->ioa_cb->ioasa;
	u32 ioasc = le32_to_cpu(ioasa->ioasc);
	u32 failing_lba = 0;

	memset(sense_buf, 0, SCSI_SENSE_BUFFERSIZE);
	cmd->scsi_cmd->result = SAM_STAT_CHECK_CONDITION;

	if (RES_IS_VSET(res->cfg_entry) &&
	    ioasc == PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC &&
	    ioasa->u.vset.failing_lba_hi != 0) {

		sense_buf[0] = 0x72;
		sense_buf[1] = PMCRAID_IOASC_SENSE_KEY(ioasc);
		sense_buf[2] = PMCRAID_IOASC_SENSE_CODE(ioasc);
		sense_buf[3] = PMCRAID_IOASC_SENSE_QUAL(ioasc);

		sense_buf[7] = 12;
		sense_buf[8] = 0;
		sense_buf[9] = 0x0A;
		sense_buf[10] = 0x80;

		failing_lba = le32_to_cpu(ioasa->u.vset.failing_lba_hi);

		sense_buf[12] = (failing_lba & 0xff000000) >> 24;
		sense_buf[13] = (failing_lba & 0x00ff0000) >> 16;
		sense_buf[14] = (failing_lba & 0x0000ff00) >> 8;
		sense_buf[15] = failing_lba & 0x000000ff;

		failing_lba = le32_to_cpu(ioasa->u.vset.failing_lba_lo);

		sense_buf[16] = (failing_lba & 0xff000000) >> 24;
		sense_buf[17] = (failing_lba & 0x00ff0000) >> 16;
		sense_buf[18] = (failing_lba & 0x0000ff00) >> 8;
		sense_buf[19] = failing_lba & 0x000000ff;
	} else {
		sense_buf[0] = 0x70;
		sense_buf[2] = PMCRAID_IOASC_SENSE_KEY(ioasc);
		sense_buf[12] = PMCRAID_IOASC_SENSE_CODE(ioasc);
		sense_buf[13] = PMCRAID_IOASC_SENSE_QUAL(ioasc);

		if (ioasc == PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC) {
			if (RES_IS_VSET(res->cfg_entry))
				failing_lba =
					le32_to_cpu(ioasa->u.
						 vset.failing_lba_lo);
			sense_buf[0] |= 0x80;
			sense_buf[3] = (failing_lba >> 24) & 0xff;
			sense_buf[4] = (failing_lba >> 16) & 0xff;
			sense_buf[5] = (failing_lba >> 8) & 0xff;
			sense_buf[6] = failing_lba & 0xff;
		}

		sense_buf[7] = 6; /* additional length */
	}
}