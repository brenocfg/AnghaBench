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
struct net_device {int dummy; } ;
struct dscc4_dev_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR0 ; 
 int /*<<< orphan*/  CCR1 ; 
 int /*<<< orphan*/  CCR2 ; 
 int HDLC_MAX_MRU ; 
 int LengthCheck ; 
 int /*<<< orphan*/  RLCR ; 
 int RxActivate ; 
 int /*<<< orphan*/  scc_writel (int,struct dscc4_dev_priv*,struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dscc4_init_registers(struct dscc4_dev_priv *dpriv,
				 struct net_device *dev)
{
	/* No interrupts, SCC core disabled. Let's relax */
	scc_writel(0x00000000, dpriv, dev, CCR0);

	scc_writel(LengthCheck | (HDLC_MAX_MRU >> 5), dpriv, dev, RLCR);

	/*
	 * No address recognition/crc-CCITT/cts enabled
	 * Shared flags transmission disabled - cf errata DS5 p.11
	 * Carrier detect disabled - cf errata p.14
	 * FIXME: carrier detection/polarity may be handled more gracefully.
	 */
	scc_writel(0x02408000, dpriv, dev, CCR1);

	/* crc not forwarded - Cf errata DS5 p.11 */
	scc_writel(0x00050008 & ~RxActivate, dpriv, dev, CCR2);
	// crc forwarded
	//scc_writel(0x00250008 & ~RxActivate, dpriv, dev, CCR2);
}