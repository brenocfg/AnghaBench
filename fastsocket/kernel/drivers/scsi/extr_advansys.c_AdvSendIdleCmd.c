#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
struct TYPE_3__ {scalar_t__ chip_type; int /*<<< orphan*/  iop_base; } ;
typedef  int /*<<< orphan*/  AdvPortAddr ;
typedef  TYPE_1__ ADV_DVC_VAR ;
typedef  scalar_t__ ADV_DCNT ;

/* Variables and functions */
 scalar_t__ ADV_CHIP_ASC3550 ; 
 int ADV_ERROR ; 
 int /*<<< orphan*/  ADV_TICKLE_B ; 
 int /*<<< orphan*/  ADV_TICKLE_NOP ; 
 int /*<<< orphan*/  ASC_MC_IDLE_CMD ; 
 int /*<<< orphan*/  ASC_MC_IDLE_CMD_PARAMETER ; 
 int /*<<< orphan*/  ASC_MC_IDLE_CMD_STATUS ; 
 int /*<<< orphan*/  AdvReadWordLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AdvWriteByteRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdvWriteDWordLramNoSwap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdvWriteWordLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IOPB_TICKLE ; 
 scalar_t__ SCSI_US_PER_MSEC ; 
 scalar_t__ SCSI_WAIT_100_MSEC ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
AdvSendIdleCmd(ADV_DVC_VAR *asc_dvc,
	       ushort idle_cmd, ADV_DCNT idle_cmd_parameter)
{
	int result;
	ADV_DCNT i, j;
	AdvPortAddr iop_base;

	iop_base = asc_dvc->iop_base;

	/*
	 * Clear the idle command status which is set by the microcode
	 * to a non-zero value to indicate when the command is completed.
	 * The non-zero result is one of the IDLE_CMD_STATUS_* values
	 */
	AdvWriteWordLram(iop_base, ASC_MC_IDLE_CMD_STATUS, (ushort)0);

	/*
	 * Write the idle command value after the idle command parameter
	 * has been written to avoid a race condition. If the order is not
	 * followed, the microcode may process the idle command before the
	 * parameters have been written to LRAM.
	 */
	AdvWriteDWordLramNoSwap(iop_base, ASC_MC_IDLE_CMD_PARAMETER,
				cpu_to_le32(idle_cmd_parameter));
	AdvWriteWordLram(iop_base, ASC_MC_IDLE_CMD, idle_cmd);

	/*
	 * Tickle the RISC to tell it to process the idle command.
	 */
	AdvWriteByteRegister(iop_base, IOPB_TICKLE, ADV_TICKLE_B);
	if (asc_dvc->chip_type == ADV_CHIP_ASC3550) {
		/*
		 * Clear the tickle value. In the ASC-3550 the RISC flag
		 * command 'clr_tickle_b' does not work unless the host
		 * value is cleared.
		 */
		AdvWriteByteRegister(iop_base, IOPB_TICKLE, ADV_TICKLE_NOP);
	}

	/* Wait for up to 100 millisecond for the idle command to timeout. */
	for (i = 0; i < SCSI_WAIT_100_MSEC; i++) {
		/* Poll once each microsecond for command completion. */
		for (j = 0; j < SCSI_US_PER_MSEC; j++) {
			AdvReadWordLram(iop_base, ASC_MC_IDLE_CMD_STATUS,
					result);
			if (result != 0)
				return result;
			udelay(1);
		}
	}

	BUG();		/* The idle command should never timeout. */
	return ADV_ERROR;
}