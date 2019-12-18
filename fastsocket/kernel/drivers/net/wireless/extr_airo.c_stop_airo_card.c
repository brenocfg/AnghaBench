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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  base_addr; struct airo_info* ml_priv; } ;
struct airo_info {int /*<<< orphan*/  tfm; int /*<<< orphan*/  shared_dma; int /*<<< orphan*/  shared; scalar_t__ pci; scalar_t__ pciaux; scalar_t__ pcimem; int /*<<< orphan*/  flags; int /*<<< orphan*/  SSID; int /*<<< orphan*/  APList; int /*<<< orphan*/  rssi; int /*<<< orphan*/  flash; int /*<<< orphan*/  txq; struct net_device* wifidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_MPI ; 
 int /*<<< orphan*/  FLAG_RADIO_DOWN ; 
 int /*<<< orphan*/  FLAG_REGISTERED ; 
 int /*<<< orphan*/  PCI_SHARED_LEN ; 
 int /*<<< orphan*/  airo_networks_free (struct airo_info*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_airo_dev (struct airo_info*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  disable_interrupts (struct airo_info*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_unmap_card (scalar_t__) ; 
 int /*<<< orphan*/  pci_free_consistent (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  takedown_proc_entry (struct net_device*,struct airo_info*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void stop_airo_card( struct net_device *dev, int freeres )
{
	struct airo_info *ai = dev->ml_priv;

	set_bit(FLAG_RADIO_DOWN, &ai->flags);
	disable_MAC(ai, 1);
	disable_interrupts(ai);
	takedown_proc_entry( dev, ai );
	if (test_bit(FLAG_REGISTERED, &ai->flags)) {
		unregister_netdev( dev );
		if (ai->wifidev) {
			unregister_netdev(ai->wifidev);
			free_netdev(ai->wifidev);
			ai->wifidev = NULL;
		}
		clear_bit(FLAG_REGISTERED, &ai->flags);
	}
	/*
	 * Clean out tx queue
	 */
	if (test_bit(FLAG_MPI, &ai->flags) && !skb_queue_empty(&ai->txq)) {
		struct sk_buff *skb = NULL;
		for (;(skb = skb_dequeue(&ai->txq));)
			dev_kfree_skb(skb);
	}

	airo_networks_free (ai);

	kfree(ai->flash);
	kfree(ai->rssi);
	kfree(ai->APList);
	kfree(ai->SSID);
	if (freeres) {
		/* PCMCIA frees this stuff, so only for PCI and ISA */
	        release_region( dev->base_addr, 64 );
		if (test_bit(FLAG_MPI, &ai->flags)) {
			if (ai->pci)
				mpi_unmap_card(ai->pci);
			if (ai->pcimem)
				iounmap(ai->pcimem);
			if (ai->pciaux)
				iounmap(ai->pciaux);
			pci_free_consistent(ai->pci, PCI_SHARED_LEN,
				ai->shared, ai->shared_dma);
		}
        }
	crypto_free_cipher(ai->tfm);
	del_airo_dev(ai);
	free_netdev( dev );
}