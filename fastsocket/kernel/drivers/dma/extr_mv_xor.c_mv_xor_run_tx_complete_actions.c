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
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ cookie; int flags; int /*<<< orphan*/  callback_param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;} ;
struct mv_xor_desc_slot {int unmap_len; int unmap_src_cnt; TYPE_3__ async_tx; struct mv_xor_desc_slot* group_head; } ;
struct mv_xor_chan {TYPE_2__* device; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  enum dma_ctrl_flags { ____Placeholder_dma_ctrl_flags } dma_ctrl_flags ;
typedef  scalar_t__ dma_cookie_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_BIDIRECTIONAL ; 
 int DMA_COMPL_SKIP_DEST_UNMAP ; 
 int DMA_COMPL_SKIP_SRC_UNMAP ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_run_dependencies (TYPE_3__*) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,int,int) ; 
 scalar_t__ mv_desc_get_dest_addr (struct mv_xor_desc_slot*) ; 
 scalar_t__ mv_desc_get_src_addr (struct mv_xor_desc_slot*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_cookie_t
mv_xor_run_tx_complete_actions(struct mv_xor_desc_slot *desc,
	struct mv_xor_chan *mv_chan, dma_cookie_t cookie)
{
	BUG_ON(desc->async_tx.cookie < 0);

	if (desc->async_tx.cookie > 0) {
		cookie = desc->async_tx.cookie;

		/* call the callback (must not sleep or submit new
		 * operations to this channel)
		 */
		if (desc->async_tx.callback)
			desc->async_tx.callback(
				desc->async_tx.callback_param);

		/* unmap dma addresses
		 * (unmap_single vs unmap_page?)
		 */
		if (desc->group_head && desc->unmap_len) {
			struct mv_xor_desc_slot *unmap = desc->group_head;
			struct device *dev =
				&mv_chan->device->pdev->dev;
			u32 len = unmap->unmap_len;
			enum dma_ctrl_flags flags = desc->async_tx.flags;
			u32 src_cnt;
			dma_addr_t addr;
			dma_addr_t dest;

			src_cnt = unmap->unmap_src_cnt;
			dest = mv_desc_get_dest_addr(unmap);
			if (!(flags & DMA_COMPL_SKIP_DEST_UNMAP)) {
				enum dma_data_direction dir;

				if (src_cnt > 1) /* is xor ? */
					dir = DMA_BIDIRECTIONAL;
				else
					dir = DMA_FROM_DEVICE;
				dma_unmap_page(dev, dest, len, dir);
			}

			if (!(flags & DMA_COMPL_SKIP_SRC_UNMAP)) {
				while (src_cnt--) {
					addr = mv_desc_get_src_addr(unmap,
								    src_cnt);
					if (addr == dest)
						continue;
					dma_unmap_page(dev, addr, len,
						       DMA_TO_DEVICE);
				}
			}
			desc->group_head = NULL;
		}
	}

	/* run dependent operations */
	dma_run_dependencies(&desc->async_tx);

	return cookie;
}