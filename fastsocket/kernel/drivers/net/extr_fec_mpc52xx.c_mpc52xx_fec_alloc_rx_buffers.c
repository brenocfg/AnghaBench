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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct bcom_task {int dummy; } ;
struct bcom_fec_bd {int /*<<< orphan*/  skb_pa; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  FEC_RX_BUFFER_SIZE ; 
 scalar_t__ bcom_prepare_next_buffer (struct bcom_task*) ; 
 int /*<<< orphan*/  bcom_queue_full (struct bcom_task*) ; 
 int /*<<< orphan*/  bcom_submit_next_buffer (struct bcom_task*,struct sk_buff*) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc52xx_fec_alloc_rx_buffers(struct net_device *dev, struct bcom_task *rxtsk)
{
	while (!bcom_queue_full(rxtsk)) {
		struct sk_buff *skb;
		struct bcom_fec_bd *bd;

		skb = dev_alloc_skb(FEC_RX_BUFFER_SIZE);
		if (skb == NULL)
			return -EAGAIN;

		/* zero out the initial receive buffers to aid debugging */
		memset(skb->data, 0, FEC_RX_BUFFER_SIZE);

		bd = (struct bcom_fec_bd *)bcom_prepare_next_buffer(rxtsk);

		bd->status = FEC_RX_BUFFER_SIZE;
		bd->skb_pa = dma_map_single(dev->dev.parent, skb->data,
				FEC_RX_BUFFER_SIZE, DMA_FROM_DEVICE);

		bcom_submit_next_buffer(rxtsk, skb);
	}

	return 0;
}