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
struct TYPE_2__ {void* pnext; scalar_t__ pbuf; } ;
struct sgiseeq_rx_desc {TYPE_1__ rdma; } ;
struct sgiseeq_private {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 void* VIRT_TO_DMA (struct sgiseeq_private*,struct sgiseeq_rx_desc*) ; 
 int /*<<< orphan*/  dma_sync_desc_dev (struct net_device*,struct sgiseeq_rx_desc*) ; 
 struct sgiseeq_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void setup_rx_ring(struct net_device *dev,
				 struct sgiseeq_rx_desc *buf,
				 int nbufs)
{
	struct sgiseeq_private *sp = netdev_priv(dev);
	int i = 0;

	while (i < (nbufs - 1)) {
		buf[i].rdma.pnext = VIRT_TO_DMA(sp, buf + i + 1);
		buf[i].rdma.pbuf = 0;
		dma_sync_desc_dev(dev, &buf[i]);
		i++;
	}
	buf[i].rdma.pbuf = 0;
	buf[i].rdma.pnext = VIRT_TO_DMA(sp, buf);
	dma_sync_desc_dev(dev, &buf[i]);
}