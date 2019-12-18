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
struct ql_rcv_buf_cb {scalar_t__ skb; } ;
struct ql3_adapter {int num_large_buffers; int /*<<< orphan*/  pdev; struct ql_rcv_buf_cb* lrg_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  memset (struct ql_rcv_buf_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmap_addr (struct ql_rcv_buf_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_len (struct ql_rcv_buf_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_free_large_buffers(struct ql3_adapter *qdev)
{
	int i = 0;
	struct ql_rcv_buf_cb *lrg_buf_cb;

	for (i = 0; i < qdev->num_large_buffers; i++) {
		lrg_buf_cb = &qdev->lrg_buf[i];
		if (lrg_buf_cb->skb) {
			dev_kfree_skb(lrg_buf_cb->skb);
			pci_unmap_single(qdev->pdev,
					 pci_unmap_addr(lrg_buf_cb, mapaddr),
					 pci_unmap_len(lrg_buf_cb, maplen),
					 PCI_DMA_FROMDEVICE);
			memset(lrg_buf_cb, 0, sizeof(struct ql_rcv_buf_cb));
		} else {
			break;
		}
	}
}