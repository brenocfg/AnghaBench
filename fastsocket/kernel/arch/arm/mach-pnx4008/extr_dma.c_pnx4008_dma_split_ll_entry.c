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
struct pnx4008_dma_ll {int ch_ctrl; unsigned long next_dma; struct pnx4008_dma_ll* next; scalar_t__ dest_addr; scalar_t__ src_addr; } ;
struct pnx4008_dma_ch_ctrl {int tr_size; int swidth; int dwidth; scalar_t__ di; scalar_t__ si; } ;

/* Variables and functions */
#define  WIDTH_BYTE 130 
#define  WIDTH_HWORD 129 
#define  WIDTH_WORD 128 
 void* pnx4008_alloc_ll_entry (unsigned long*) ; 

void pnx4008_dma_split_ll_entry(struct pnx4008_dma_ll * cur_ll,
				struct pnx4008_dma_ch_ctrl * ctrl)
{
	int new_len = ctrl->tr_size, num_entries = 0;
	int old_len = new_len;
	int src_width, dest_width, count = 1;

	switch (ctrl->swidth) {
	case WIDTH_BYTE:
		src_width = 1;
		break;
	case WIDTH_HWORD:
		src_width = 2;
		break;
	case WIDTH_WORD:
		src_width = 4;
		break;
	default:
		return;
	}

	switch (ctrl->dwidth) {
	case WIDTH_BYTE:
		dest_width = 1;
		break;
	case WIDTH_HWORD:
		dest_width = 2;
		break;
	case WIDTH_WORD:
		dest_width = 4;
		break;
	default:
		return;
	}

	while (new_len > 0x7FF) {
		num_entries++;
		new_len = (ctrl->tr_size + num_entries) / (num_entries + 1);
	}
	if (num_entries != 0) {
		struct pnx4008_dma_ll *ll = NULL;
		cur_ll->ch_ctrl &= ~0x7ff;
		cur_ll->ch_ctrl |= new_len;
		if (!cur_ll->next) {
			while (num_entries) {
				if (!ll) {
					cur_ll->next =
					    pnx4008_alloc_ll_entry(&cur_ll->
								   next_dma);
					ll = cur_ll->next;
				} else {
					ll->next =
					    pnx4008_alloc_ll_entry(&ll->
								   next_dma);
					ll = ll->next;
				}

				if (ctrl->si)
					ll->src_addr =
					    cur_ll->src_addr +
					    src_width * new_len * count;
				else
					ll->src_addr = cur_ll->src_addr;
				if (ctrl->di)
					ll->dest_addr =
					    cur_ll->dest_addr +
					    dest_width * new_len * count;
				else
					ll->dest_addr = cur_ll->dest_addr;
				ll->ch_ctrl = cur_ll->ch_ctrl & 0x7fffffff;
				ll->next_dma = 0;
				ll->next = NULL;
				num_entries--;
				count++;
			}
		} else {
			struct pnx4008_dma_ll *ll_old = cur_ll->next;
			unsigned long ll_dma_old = cur_ll->next_dma;
			while (num_entries) {
				if (!ll) {
					cur_ll->next =
					    pnx4008_alloc_ll_entry(&cur_ll->
								   next_dma);
					ll = cur_ll->next;
				} else {
					ll->next =
					    pnx4008_alloc_ll_entry(&ll->
								   next_dma);
					ll = ll->next;
				}

				if (ctrl->si)
					ll->src_addr =
					    cur_ll->src_addr +
					    src_width * new_len * count;
				else
					ll->src_addr = cur_ll->src_addr;
				if (ctrl->di)
					ll->dest_addr =
					    cur_ll->dest_addr +
					    dest_width * new_len * count;
				else
					ll->dest_addr = cur_ll->dest_addr;
				ll->ch_ctrl = cur_ll->ch_ctrl & 0x7fffffff;
				ll->next_dma = 0;
				ll->next = NULL;
				num_entries--;
				count++;
			}

			ll->next_dma = ll_dma_old;
			ll->next = ll_old;
		}
		/* adjust last length/tc */
		ll->ch_ctrl = cur_ll->ch_ctrl & (~0x7ff);
		ll->ch_ctrl |= old_len - new_len * (count - 1);
		cur_ll->ch_ctrl &= 0x7fffffff;
	}
}