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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/ * cb; } ;
struct nes_rskb_cb {scalar_t__ busaddr; int /*<<< orphan*/  maplen; } ;
struct nes_device {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nes_mgt_free_skb(struct nes_device *nesdev, struct sk_buff *skb, u32 dir)
{
	struct nes_rskb_cb *cb;

	cb = (struct nes_rskb_cb *)&skb->cb[0];
	pci_unmap_single(nesdev->pcidev, cb->busaddr, cb->maplen, dir);
	cb->busaddr = 0;
	dev_kfree_skb_any(skb);
}