#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct vxge_hw_fifo_txd {int /*<<< orphan*/  control_0; scalar_t__ buffer_pointer; int /*<<< orphan*/  control_1; } ;
struct __vxge_hw_fifo_txdl_priv {int frags; scalar_t__ alloc_frags; } ;
struct __vxge_hw_channel {int dummy; } ;
struct __vxge_hw_fifo {TYPE_1__* stats; int /*<<< orphan*/  tx_intr_num; int /*<<< orphan*/  interrupt_type; struct __vxge_hw_channel channel; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  total_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_HW_FIFO_TXD_BUFFER_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  VXGE_HW_FIFO_TXD_GATHER_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VXGE_HW_FIFO_TXD_GATHER_CODE_FIRST ; 
 int /*<<< orphan*/  VXGE_HW_FIFO_TXD_GATHER_CODE_LAST ; 
 int /*<<< orphan*/  VXGE_HW_FIFO_TXD_INT_NUMBER (int /*<<< orphan*/ ) ; 
 struct __vxge_hw_fifo_txdl_priv* __vxge_hw_fifo_txdl_priv (struct __vxge_hw_fifo*,void*) ; 
 int /*<<< orphan*/  vxge_assert (int) ; 

void vxge_hw_fifo_txdl_buffer_set(struct __vxge_hw_fifo *fifo,
				  void *txdlh, u32 frag_idx,
				  dma_addr_t dma_pointer, u32 size)
{
	struct __vxge_hw_fifo_txdl_priv *txdl_priv;
	struct vxge_hw_fifo_txd *txdp, *txdp_last;
	struct __vxge_hw_channel *channel;

	channel = &fifo->channel;

	txdl_priv = __vxge_hw_fifo_txdl_priv(fifo, txdlh);
	txdp = (struct vxge_hw_fifo_txd *)txdlh  +  txdl_priv->frags;

	if (frag_idx != 0)
		txdp->control_0 = txdp->control_1 = 0;
	else {
		txdp->control_0 |= VXGE_HW_FIFO_TXD_GATHER_CODE(
			VXGE_HW_FIFO_TXD_GATHER_CODE_FIRST);
		txdp->control_1 |= fifo->interrupt_type;
		txdp->control_1 |= VXGE_HW_FIFO_TXD_INT_NUMBER(
			fifo->tx_intr_num);
		if (txdl_priv->frags) {
			txdp_last = (struct vxge_hw_fifo_txd *)txdlh  +
			(txdl_priv->frags - 1);
			txdp_last->control_0 |= VXGE_HW_FIFO_TXD_GATHER_CODE(
				VXGE_HW_FIFO_TXD_GATHER_CODE_LAST);
		}
	}

	vxge_assert(frag_idx < txdl_priv->alloc_frags);

	txdp->buffer_pointer = (u64)dma_pointer;
	txdp->control_0 |= VXGE_HW_FIFO_TXD_BUFFER_SIZE(size);
	fifo->stats->total_buffers++;
	txdl_priv->frags++;
}