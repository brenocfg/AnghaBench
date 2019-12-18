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
struct sbmacdma {int sbdma_dscrtable_phys; int /*<<< orphan*/  sbdma_dscrtable; int /*<<< orphan*/  sbdma_remptr; int /*<<< orphan*/  sbdma_addptr; int /*<<< orphan*/  sbdma_dscrbase; int /*<<< orphan*/  sbdma_config0; int /*<<< orphan*/  sbdma_maxdescr; int /*<<< orphan*/  sbdma_config1; int /*<<< orphan*/  sbdma_int_pktcnt; int /*<<< orphan*/  sbdma_int_timeout; } ;

/* Variables and functions */
 int M_DMA_EOP_INT_EN ; 
 int V_DMA_INT_PKTCNT (int /*<<< orphan*/ ) ; 
 int V_DMA_INT_TIMEOUT (int /*<<< orphan*/ ) ; 
 int V_DMA_RINGSZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sbdma_channel_start(struct sbmacdma *d, int rxtx)
{
	/*
	 * Turn on the DMA channel
	 */

#ifdef CONFIG_SBMAC_COALESCE
	__raw_writeq(V_DMA_INT_TIMEOUT(d->sbdma_int_timeout) |
		       0, d->sbdma_config1);
	__raw_writeq(M_DMA_EOP_INT_EN |
		       V_DMA_RINGSZ(d->sbdma_maxdescr) |
		       V_DMA_INT_PKTCNT(d->sbdma_int_pktcnt) |
		       0, d->sbdma_config0);
#else
	__raw_writeq(0, d->sbdma_config1);
	__raw_writeq(V_DMA_RINGSZ(d->sbdma_maxdescr) |
		       0, d->sbdma_config0);
#endif

	__raw_writeq(d->sbdma_dscrtable_phys, d->sbdma_dscrbase);

	/*
	 * Initialize ring pointers
	 */

	d->sbdma_addptr = d->sbdma_dscrtable;
	d->sbdma_remptr = d->sbdma_dscrtable;
}