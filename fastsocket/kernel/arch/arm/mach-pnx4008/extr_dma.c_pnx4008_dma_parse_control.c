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
struct pnx4008_dma_ch_ctrl {unsigned long tr_size; int sbsize; int dbsize; unsigned long src_ahb1; unsigned long dest_ahb1; unsigned long si; unsigned long di; unsigned long priv_mode; unsigned long bufferable; unsigned long cacheable; unsigned long tc_mask; void* dwidth; void* swidth; } ;

/* Variables and functions */
 int EINVAL ; 
 void* WIDTH_BYTE ; 
 void* WIDTH_HWORD ; 
 void* WIDTH_WORD ; 

int pnx4008_dma_parse_control(unsigned long ctrl,
			      struct pnx4008_dma_ch_ctrl * ch_ctrl)
{
	int err = 0;

	if (!ch_ctrl) {
		err = -EINVAL;
		goto out;
	}

	ch_ctrl->tr_size = ctrl & 0x7ff;
	ctrl >>= 12;

	ch_ctrl->sbsize = 1 << (ctrl & 7);
	if (ch_ctrl->sbsize > 1)
		ch_ctrl->sbsize <<= 1;
	ctrl >>= 3;

	ch_ctrl->dbsize = 1 << (ctrl & 7);
	if (ch_ctrl->dbsize > 1)
		ch_ctrl->dbsize <<= 1;
	ctrl >>= 3;

	switch (ctrl & 7) {
	case 0:
		ch_ctrl->swidth = WIDTH_BYTE;
		break;
	case 1:
		ch_ctrl->swidth = WIDTH_HWORD;
		break;
	case 2:
		ch_ctrl->swidth = WIDTH_WORD;
		break;
	default:
		err = -EINVAL;
		goto out;
	}
	ctrl >>= 3;

	switch (ctrl & 7) {
	case 0:
		ch_ctrl->dwidth = WIDTH_BYTE;
		break;
	case 1:
		ch_ctrl->dwidth = WIDTH_HWORD;
		break;
	case 2:
		ch_ctrl->dwidth = WIDTH_WORD;
		break;
	default:
		err = -EINVAL;
		goto out;
	}
	ctrl >>= 3;

	ch_ctrl->src_ahb1 = ctrl & 1;
	ctrl >>= 1;

	ch_ctrl->dest_ahb1 = ctrl & 1;
	ctrl >>= 1;

	ch_ctrl->si = ctrl & 1;
	ctrl >>= 1;

	ch_ctrl->di = ctrl & 1;
	ctrl >>= 1;

	ch_ctrl->priv_mode = ctrl & 1;
	ctrl >>= 1;

	ch_ctrl->bufferable = ctrl & 1;
	ctrl >>= 1;

	ch_ctrl->cacheable = ctrl & 1;
	ctrl >>= 1;

	ch_ctrl->tc_mask = ctrl & 1;

out:
	return err;
}