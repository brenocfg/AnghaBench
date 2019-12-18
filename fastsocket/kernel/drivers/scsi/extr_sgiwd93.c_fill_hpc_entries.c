#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long this_residual; unsigned long dma_handle; void* ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct ip22_hostdata {struct hpc_chunk* cpu; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {unsigned long pbuf; unsigned long cntinfo; } ;
struct hpc_chunk {TYPE_2__ desc; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DIR (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned long HPCDMA_EOX ; 
 int /*<<< orphan*/  dma_cache_sync (int /*<<< orphan*/ ,struct hpc_chunk*,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long dma_map_single (int /*<<< orphan*/ ,void*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void fill_hpc_entries(struct ip22_hostdata *hd, struct scsi_cmnd *cmd, int din)
{
	unsigned long len = cmd->SCp.this_residual;
	void *addr = cmd->SCp.ptr;
	dma_addr_t physaddr;
	unsigned long count;
	struct hpc_chunk *hcp;

	physaddr = dma_map_single(hd->dev, addr, len, DMA_DIR(din));
	cmd->SCp.dma_handle = physaddr;
	hcp = hd->cpu;

	while (len) {
		/*
		 * even cntinfo could be up to 16383, without
		 * magic only 8192 works correctly
		 */
		count = len > 8192 ? 8192 : len;
		hcp->desc.pbuf = physaddr;
		hcp->desc.cntinfo = count;
		hcp++;
		len -= count;
		physaddr += count;
	}

	/*
	 * To make sure, if we trip an HPC bug, that we transfer every single
	 * byte, we tag on an extra zero length dma descriptor at the end of
	 * the chain.
	 */
	hcp->desc.pbuf = 0;
	hcp->desc.cntinfo = HPCDMA_EOX;
	dma_cache_sync(hd->dev, hd->cpu,
		       (unsigned long)(hcp + 1) - (unsigned long)hd->cpu,
		       DMA_TO_DEVICE);
}