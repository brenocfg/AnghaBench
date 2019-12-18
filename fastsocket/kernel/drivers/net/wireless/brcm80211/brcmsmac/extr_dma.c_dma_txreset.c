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
typedef  int u32 ;
struct dma_pub {int dummy; } ;
struct dma_info {scalar_t__ ntxd; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  D64_XC_SE ; 
 int D64_XS0_XS_DISABLED ; 
 int D64_XS0_XS_IDLE ; 
 int D64_XS0_XS_MASK ; 
 int D64_XS0_XS_STOPPED ; 
 int /*<<< orphan*/  DMA64TXREGOFFS (struct dma_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPINWAIT (int,int) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  status0 ; 
 int /*<<< orphan*/  udelay (int) ; 

bool dma_txreset(struct dma_pub *pub)
{
	struct dma_info *di = (struct dma_info *)pub;
	u32 status;

	if (di->ntxd == 0)
		return true;

	/* suspend tx DMA first */
	bcma_write32(di->core, DMA64TXREGOFFS(di, control), D64_XC_SE);
	SPINWAIT(((status =
		   (bcma_read32(di->core, DMA64TXREGOFFS(di, status0)) &
		    D64_XS0_XS_MASK)) != D64_XS0_XS_DISABLED) &&
		  (status != D64_XS0_XS_IDLE) && (status != D64_XS0_XS_STOPPED),
		 10000);

	bcma_write32(di->core, DMA64TXREGOFFS(di, control), 0);
	SPINWAIT(((status =
		   (bcma_read32(di->core, DMA64TXREGOFFS(di, status0)) &
		    D64_XS0_XS_MASK)) != D64_XS0_XS_DISABLED), 10000);

	/* wait for the last transaction to complete */
	udelay(300);

	return status == D64_XS0_XS_DISABLED;
}