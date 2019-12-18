#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  datalen; void* bufaddrl; void* bufaddrh; } ;
struct rxdesc {TYPE_2__ desc1; scalar_t__* dw; } ;
struct jme_ring {struct jme_buffer_info* bufinf; struct rxdesc* desc; } ;
struct jme_buffer_info {int /*<<< orphan*/  len; scalar_t__ mapping; } ;
struct jme_adapter {TYPE_1__* dev; struct jme_ring* rxring; } ;
typedef  int __u64 ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int NETIF_F_HIGHDMA ; 
 int RXFLAG_64BIT ; 
 int RXFLAG_INT ; 
 int RXFLAG_OWN ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
jme_set_clean_rxdesc(struct jme_adapter *jme, int i)
{
	struct jme_ring *rxring = &(jme->rxring[0]);
	register struct rxdesc *rxdesc = rxring->desc;
	struct jme_buffer_info *rxbi = rxring->bufinf;
	rxdesc += i;
	rxbi += i;

	rxdesc->dw[0] = 0;
	rxdesc->dw[1] = 0;
	rxdesc->desc1.bufaddrh	= cpu_to_le32((__u64)rxbi->mapping >> 32);
	rxdesc->desc1.bufaddrl	= cpu_to_le32(
					(__u64)rxbi->mapping & 0xFFFFFFFFUL);
	rxdesc->desc1.datalen	= cpu_to_le16(rxbi->len);
	if (jme->dev->features & NETIF_F_HIGHDMA)
		rxdesc->desc1.flags = RXFLAG_64BIT;
	wmb();
	rxdesc->desc1.flags	|= RXFLAG_OWN | RXFLAG_INT;
}