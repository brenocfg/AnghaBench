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
struct pnx4008_dma_ch_ctrl {int tc_mask; int cacheable; int bufferable; int priv_mode; int di; int si; int dest_ahb1; int src_ahb1; int dwidth; int swidth; int dbsize; int sbsize; int tr_size; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
#define  WIDTH_BYTE 130 
#define  WIDTH_HWORD 129 
#define  WIDTH_WORD 128 

int pnx4008_dma_pack_control(const struct pnx4008_dma_ch_ctrl * ch_ctrl,
			     unsigned long *ctrl)
{
	int i = 0, dbsize, sbsize, err = 0;

	if (!ctrl || !ch_ctrl) {
		err = -EINVAL;
		goto out;
	}

	*ctrl = 0;

	switch (ch_ctrl->tc_mask) {
	case 0:
		break;
	case 1:
		*ctrl |= (1 << 31);
		break;

	default:
		err = -EINVAL;
		goto out;
	}

	switch (ch_ctrl->cacheable) {
	case 0:
		break;
	case 1:
		*ctrl |= (1 << 30);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_ctrl->bufferable) {
	case 0:
		break;
	case 1:
		*ctrl |= (1 << 29);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_ctrl->priv_mode) {
	case 0:
		break;
	case 1:
		*ctrl |= (1 << 28);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_ctrl->di) {
	case 0:
		break;
	case 1:
		*ctrl |= (1 << 27);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_ctrl->si) {
	case 0:
		break;
	case 1:
		*ctrl |= (1 << 26);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_ctrl->dest_ahb1) {
	case 0:
		break;
	case 1:
		*ctrl |= (1 << 25);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_ctrl->src_ahb1) {
	case 0:
		break;
	case 1:
		*ctrl |= (1 << 24);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_ctrl->dwidth) {
	case WIDTH_BYTE:
		*ctrl &= ~(7 << 21);
		break;
	case WIDTH_HWORD:
		*ctrl &= ~(7 << 21);
		*ctrl |= (1 << 21);
		break;
	case WIDTH_WORD:
		*ctrl &= ~(7 << 21);
		*ctrl |= (2 << 21);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	switch (ch_ctrl->swidth) {
	case WIDTH_BYTE:
		*ctrl &= ~(7 << 18);
		break;
	case WIDTH_HWORD:
		*ctrl &= ~(7 << 18);
		*ctrl |= (1 << 18);
		break;
	case WIDTH_WORD:
		*ctrl &= ~(7 << 18);
		*ctrl |= (2 << 18);
		break;

	default:
		err = -EINVAL;
		goto out;
	}
	dbsize = ch_ctrl->dbsize;
	while (!(dbsize & 1)) {
		i++;
		dbsize >>= 1;
	}
	if (ch_ctrl->dbsize != 1 || i > 8 || i == 1) {
		err = -EINVAL;
		goto out;
	} else if (i > 1)
		i--;
	*ctrl &= ~(7 << 15);
	*ctrl |= (i << 15);

	sbsize = ch_ctrl->sbsize;
	while (!(sbsize & 1)) {
		i++;
		sbsize >>= 1;
	}
	if (ch_ctrl->sbsize != 1 || i > 8 || i == 1) {
		err = -EINVAL;
		goto out;
	} else if (i > 1)
		i--;
	*ctrl &= ~(7 << 12);
	*ctrl |= (i << 12);

	if (ch_ctrl->tr_size > 0x7ff) {
		err = -E2BIG;
		goto out;
	}
	*ctrl &= ~0x7ff;
	*ctrl |= ch_ctrl->tr_size & 0x7ff;

out:
	return err;
}