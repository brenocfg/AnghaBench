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
typedef  int u32 ;
struct sis900_private {scalar_t__ chipset_rev; } ;
struct net_device {long base_addr; } ;

/* Variables and functions */
 int PESEL ; 
 int RESET ; 
 int RND_CNT ; 
 int RxRCMP ; 
 int RxRESET ; 
 scalar_t__ SIS635A_900_REV ; 
 scalar_t__ SIS900B_900_REV ; 
 int TxRCMP ; 
 int TxRESET ; 
 scalar_t__ cfg ; 
 scalar_t__ cr ; 
 scalar_t__ ier ; 
 scalar_t__ imr ; 
 int inl (scalar_t__) ; 
 scalar_t__ isr ; 
 struct sis900_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 scalar_t__ rfcr ; 

__attribute__((used)) static void sis900_reset(struct net_device *net_dev)
{
	struct sis900_private *sis_priv = netdev_priv(net_dev);
	long ioaddr = net_dev->base_addr;
	int i = 0;
	u32 status = TxRCMP | RxRCMP;

	outl(0, ioaddr + ier);
	outl(0, ioaddr + imr);
	outl(0, ioaddr + rfcr);

	outl(RxRESET | TxRESET | RESET | inl(ioaddr + cr), ioaddr + cr);

	/* Check that the chip has finished the reset. */
	while (status && (i++ < 1000)) {
		status ^= (inl(isr + ioaddr) & status);
	}

	if( (sis_priv->chipset_rev >= SIS635A_900_REV) ||
			(sis_priv->chipset_rev == SIS900B_900_REV) )
		outl(PESEL | RND_CNT, ioaddr + cfg);
	else
		outl(PESEL, ioaddr + cfg);
}