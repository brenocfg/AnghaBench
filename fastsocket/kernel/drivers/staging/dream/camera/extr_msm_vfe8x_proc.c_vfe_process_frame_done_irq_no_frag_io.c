#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ hwRegPingAddress; scalar_t__ hwRegPongAddress; } ;
struct TYPE_4__ {scalar_t__ hwRegPingAddress; scalar_t__ hwRegPongAddress; } ;
struct vfe_output_path_combo {int cbcrStatusBit; TYPE_2__ cbcrPath; TYPE_1__ yPath; } ;
struct TYPE_6__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,int) ; 
 scalar_t__ VFE_BUS_PINGPONG_STATUS ; 
 TYPE_3__* ctrl ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void vfe_process_frame_done_irq_no_frag_io(
	struct vfe_output_path_combo *in, uint32_t *pNextAddr,
	uint32_t *pdestRenderAddr)
{
	uint32_t busPingPongStatus;
	uint32_t tempAddress;

	/* 1. read hw status register. */
	busPingPongStatus =
		readl(ctrl->vfebase + VFE_BUS_PINGPONG_STATUS);

	CDBG("hardware status is 0x%x\n", busPingPongStatus);

	/* 2. determine ping or pong */
	/* use cbcr status */
	busPingPongStatus = busPingPongStatus & (1<<(in->cbcrStatusBit));

	/* 3. read out address and update address */
	if (busPingPongStatus == 0) {
		/* hw is working on ping, render pong buffer */
		/* a. read out pong address */
		/* read out y address. */
		tempAddress = readl(in->yPath.hwRegPongAddress);

		CDBG("pong 1 addr = 0x%x\n", tempAddress);
		*pdestRenderAddr++ = tempAddress;
		/* read out cbcr address. */
		tempAddress = readl(in->cbcrPath.hwRegPongAddress);

		CDBG("pong 2 addr = 0x%x\n", tempAddress);
		*pdestRenderAddr = tempAddress;

		/* b. update pong address */
		writel(*pNextAddr++, in->yPath.hwRegPongAddress);
		writel(*pNextAddr, in->cbcrPath.hwRegPongAddress);
	} else {
		/* hw is working on pong, render ping buffer */

		/* a. read out ping address */
		tempAddress = readl(in->yPath.hwRegPingAddress);
		CDBG("ping 1 addr = 0x%x\n", tempAddress);
		*pdestRenderAddr++ = tempAddress;
		tempAddress = readl(in->cbcrPath.hwRegPingAddress);

		CDBG("ping 2 addr = 0x%x\n", tempAddress);
		*pdestRenderAddr = tempAddress;

		/* b. update ping address */
		writel(*pNextAddr++, in->yPath.hwRegPingAddress);
		CDBG("NextAddress = 0x%x\n", *pNextAddr);
		writel(*pNextAddr, in->cbcrPath.hwRegPingAddress);
	}
}