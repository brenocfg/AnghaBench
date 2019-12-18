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
struct efx_special_buffer {int entries; int index; int dma_addr; int /*<<< orphan*/  addr; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int EFX_BUF_SIZE ; 
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 int /*<<< orphan*/  EFX_POPULATE_QWORD_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_AZ_BUF_ADR_FBUF ; 
 int /*<<< orphan*/  FRF_AZ_BUF_ADR_REGION ; 
 int /*<<< orphan*/  FRF_AZ_BUF_OWNER_ID_FBUF ; 
 int /*<<< orphan*/  efx_write_buf_tbl (struct efx_nic*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned long long) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static void
efx_init_special_buffer(struct efx_nic *efx, struct efx_special_buffer *buffer)
{
	efx_qword_t buf_desc;
	unsigned int index;
	dma_addr_t dma_addr;
	int i;

	EFX_BUG_ON_PARANOID(!buffer->addr);

	/* Write buffer descriptors to NIC */
	for (i = 0; i < buffer->entries; i++) {
		index = buffer->index + i;
		dma_addr = buffer->dma_addr + (i * EFX_BUF_SIZE);
		netif_dbg(efx, probe, efx->net_dev,
			  "mapping special buffer %d at %llx\n",
			  index, (unsigned long long)dma_addr);
		EFX_POPULATE_QWORD_3(buf_desc,
				     FRF_AZ_BUF_ADR_REGION, 0,
				     FRF_AZ_BUF_ADR_FBUF, dma_addr >> 12,
				     FRF_AZ_BUF_OWNER_ID_FBUF, 0);
		efx_write_buf_tbl(efx, &buf_desc, index);
	}
}