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
struct vnic_rq {int /*<<< orphan*/  vdev; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {unsigned int mtu; } ;
struct enic {int /*<<< orphan*/  pdev; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 unsigned int VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  enic_queue_rq_desc (struct vnic_rq*,struct sk_buff*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct enic* vnic_dev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_rq_alloc_buf(struct vnic_rq *rq)
{
	struct enic *enic = vnic_dev_priv(rq->vdev);
	struct net_device *netdev = enic->netdev;
	struct sk_buff *skb;
	unsigned int len = netdev->mtu + VLAN_ETH_HLEN;
	unsigned int os_buf_index = 0;
	dma_addr_t dma_addr;

	skb = netdev_alloc_skb_ip_align(netdev, len);
	if (!skb)
		return -ENOMEM;

	dma_addr = pci_map_single(enic->pdev, skb->data,
		len, PCI_DMA_FROMDEVICE);

	enic_queue_rq_desc(rq, skb, os_buf_index,
		dma_addr, len);

	return 0;
}