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
struct pnx4008_dma_ch_config {int halt; int active; int lock; int itc; int ie; int flow_cntrl; int dest_per; int src_per; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FC_MEM2MEM_DMA 135 
#define  FC_MEM2PER_DMA 134 
#define  FC_MEM2PER_PER 133 
#define  FC_PER2MEM_DMA 132 
#define  FC_PER2MEM_PER 131 
#define  FC_PER2PER_DMA 130 
#define  FC_PER2PER_DPER 129 
#define  FC_PER2PER_SPER 128 

int pnx4008_dma_pack_config(const struct pnx4008_dma_ch_config * ch_cfg,
			    unsigned long *cfg)
{
	int err = 0;

	if (!cfg || !ch_cfg) {
		err = -EINVAL;
		goto out;
	}

	*cfg = 0;

	switch (ch_cfg->halt) {
	case 0:
		break;
	case 1:
		*cfg |= (1 << 18);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_cfg->active) {
	case 0:
		break;
	case 1:
		*cfg |= (1 << 17);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_cfg->lock) {
	case 0:
		break;
	case 1:
		*cfg |= (1 << 16);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_cfg->itc) {
	case 0:
		break;
	case 1:
		*cfg |= (1 << 15);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_cfg->ie) {
	case 0:
		break;
	case 1:
		*cfg |= (1 << 14);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_cfg->flow_cntrl) {
	case FC_MEM2MEM_DMA:
		*cfg &= ~(7 << 11);
		break;
	case FC_MEM2PER_DMA:
		*cfg &= ~(7 << 11);
		*cfg |= (1 << 11);
		break;
	case FC_PER2MEM_DMA:
		*cfg &= ~(7 << 11);
		*cfg |= (2 << 11);
		break;
	case FC_PER2PER_DMA:
		*cfg &= ~(7 << 11);
		*cfg |= (3 << 11);
		break;
	case FC_PER2PER_DPER:
		*cfg &= ~(7 << 11);
		*cfg |= (4 << 11);
		break;
	case FC_MEM2PER_PER:
		*cfg &= ~(7 << 11);
		*cfg |= (5 << 11);
		break;
	case FC_PER2MEM_PER:
		*cfg &= ~(7 << 11);
		*cfg |= (6 << 11);
		break;
	case FC_PER2PER_SPER:
		*cfg |= (7 << 11);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	*cfg &= ~(0x1f << 6);
	*cfg |= ((ch_cfg->dest_per & 0x1f) << 6);

	*cfg &= ~(0x1f << 1);
	*cfg |= ((ch_cfg->src_per & 0x1f) << 1);

out:
	return err;
}