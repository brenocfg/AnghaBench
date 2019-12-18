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
typedef  int u32 ;
struct radeon_device {int family; int usec_timeout; TYPE_1__* mc_fw; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int EINVAL ; 
 int /*<<< orphan*/  MC_SEQ_IO_DEBUG_DATA ; 
 int /*<<< orphan*/  MC_SEQ_IO_DEBUG_INDEX ; 
 int /*<<< orphan*/  MC_SEQ_SUP_CNTL ; 
 int /*<<< orphan*/  MC_SEQ_SUP_PGM ; 
 int /*<<< orphan*/  MC_SEQ_TRAIN_WAKEUP_CNTL ; 
 int /*<<< orphan*/  MC_SHARED_BLACKOUT_CNTL ; 
 int OLAND_MC_UCODE_SIZE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RUN_MASK ; 
 int SI_MC_UCODE_SIZE ; 
 int TAHITI_IO_MC_REGS_SIZE ; 
 int TRAIN_DONE_D0 ; 
 int TRAIN_DONE_D1 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oland_io_mc_regs ; 
 int /*<<< orphan*/  pitcairn_io_mc_regs ; 
 int /*<<< orphan*/  tahiti_io_mc_regs ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  verde_io_mc_regs ; 

__attribute__((used)) static int si_mc_load_microcode(struct radeon_device *rdev)
{
	const __be32 *fw_data;
	u32 running, blackout = 0;
	u32 *io_mc_regs;
	int i, ucode_size, regs_size;

	if (!rdev->mc_fw)
		return -EINVAL;

	switch (rdev->family) {
	case CHIP_TAHITI:
		io_mc_regs = (u32 *)&tahiti_io_mc_regs;
		ucode_size = SI_MC_UCODE_SIZE;
		regs_size = TAHITI_IO_MC_REGS_SIZE;
		break;
	case CHIP_PITCAIRN:
		io_mc_regs = (u32 *)&pitcairn_io_mc_regs;
		ucode_size = SI_MC_UCODE_SIZE;
		regs_size = TAHITI_IO_MC_REGS_SIZE;
		break;
	case CHIP_VERDE:
	default:
		io_mc_regs = (u32 *)&verde_io_mc_regs;
		ucode_size = SI_MC_UCODE_SIZE;
		regs_size = TAHITI_IO_MC_REGS_SIZE;
		break;
	case CHIP_OLAND:
		io_mc_regs = (u32 *)&oland_io_mc_regs;
		ucode_size = OLAND_MC_UCODE_SIZE;
		regs_size = TAHITI_IO_MC_REGS_SIZE;
		break;
	}

	running = RREG32(MC_SEQ_SUP_CNTL) & RUN_MASK;

	if (running == 0) {
		if (running) {
			blackout = RREG32(MC_SHARED_BLACKOUT_CNTL);
			WREG32(MC_SHARED_BLACKOUT_CNTL, blackout | 1);
		}

		/* reset the engine and set to writable */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000010);

		/* load mc io regs */
		for (i = 0; i < regs_size; i++) {
			WREG32(MC_SEQ_IO_DEBUG_INDEX, io_mc_regs[(i << 1)]);
			WREG32(MC_SEQ_IO_DEBUG_DATA, io_mc_regs[(i << 1) + 1]);
		}
		/* load the MC ucode */
		fw_data = (const __be32 *)rdev->mc_fw->data;
		for (i = 0; i < ucode_size; i++)
			WREG32(MC_SEQ_SUP_PGM, be32_to_cpup(fw_data++));

		/* put the engine back into the active state */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000004);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000001);

		/* wait for training to complete */
		for (i = 0; i < rdev->usec_timeout; i++) {
			if (RREG32(MC_SEQ_TRAIN_WAKEUP_CNTL) & TRAIN_DONE_D0)
				break;
			udelay(1);
		}
		for (i = 0; i < rdev->usec_timeout; i++) {
			if (RREG32(MC_SEQ_TRAIN_WAKEUP_CNTL) & TRAIN_DONE_D1)
				break;
			udelay(1);
		}

		if (running)
			WREG32(MC_SHARED_BLACKOUT_CNTL, blackout);
	}

	return 0;
}