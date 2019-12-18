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
struct dma_device {int /*<<< orphan*/  dev; struct dma_async_tx_descriptor* (* device_prep_dma_memcpy ) (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,unsigned long) ;} ;
struct dma_chan {int /*<<< orphan*/  local; struct dma_device* device; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  (* tx_submit ) (struct dma_async_tx_descriptor*) ;int /*<<< orphan*/ * callback; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {size_t bytes_transferred; int /*<<< orphan*/  memcpy_count; } ;

/* Variables and functions */
 unsigned long DMA_COMPL_DEST_UNMAP_SINGLE ; 
 unsigned long DMA_COMPL_SRC_UNMAP_SINGLE ; 
 unsigned long DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int get_cpu () ; 
 TYPE_1__* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 struct dma_async_tx_descriptor* stub1 (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,unsigned long) ; 
 int /*<<< orphan*/  stub2 (struct dma_async_tx_descriptor*) ; 

dma_cookie_t
dma_async_memcpy_buf_to_buf(struct dma_chan *chan, void *dest,
			void *src, size_t len)
{
	struct dma_device *dev = chan->device;
	struct dma_async_tx_descriptor *tx;
	dma_addr_t dma_dest, dma_src;
	dma_cookie_t cookie;
	int cpu;
	unsigned long flags;

	dma_src = dma_map_single(dev->dev, src, len, DMA_TO_DEVICE);
	dma_dest = dma_map_single(dev->dev, dest, len, DMA_FROM_DEVICE);
	flags = DMA_CTRL_ACK |
		DMA_COMPL_SRC_UNMAP_SINGLE |
		DMA_COMPL_DEST_UNMAP_SINGLE;
	tx = dev->device_prep_dma_memcpy(chan, dma_dest, dma_src, len, flags);

	if (!tx) {
		dma_unmap_single(dev->dev, dma_src, len, DMA_TO_DEVICE);
		dma_unmap_single(dev->dev, dma_dest, len, DMA_FROM_DEVICE);
		return -ENOMEM;
	}

	tx->callback = NULL;
	cookie = tx->tx_submit(tx);

	cpu = get_cpu();
	per_cpu_ptr(chan->local, cpu)->bytes_transferred += len;
	per_cpu_ptr(chan->local, cpu)->memcpy_count++;
	put_cpu();

	return cookie;
}