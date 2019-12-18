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
struct gem {int rx_buf_sz; int mac_rx_cfg; scalar_t__ regs; scalar_t__ has_wol; TYPE_1__* dev; } ;
struct TYPE_2__ {unsigned char* dev_addr; } ;

/* Variables and functions */
 scalar_t__ MAC_ADDR0 ; 
 scalar_t__ MAC_ADDR1 ; 
 scalar_t__ MAC_ADDR2 ; 
 scalar_t__ MAC_ADDR3 ; 
 scalar_t__ MAC_ADDR4 ; 
 scalar_t__ MAC_ADDR5 ; 
 scalar_t__ MAC_ADDR6 ; 
 scalar_t__ MAC_ADDR7 ; 
 scalar_t__ MAC_ADDR8 ; 
 scalar_t__ MAC_AERR ; 
 scalar_t__ MAC_AF0MSK ; 
 scalar_t__ MAC_AF21MSK ; 
 scalar_t__ MAC_AFILT0 ; 
 scalar_t__ MAC_AFILT1 ; 
 scalar_t__ MAC_AFILT2 ; 
 scalar_t__ MAC_ATTLIM ; 
 scalar_t__ MAC_DTIMER ; 
 scalar_t__ MAC_ECOLL ; 
 scalar_t__ MAC_FASUCC ; 
 scalar_t__ MAC_FCSERR ; 
 scalar_t__ MAC_IPG0 ; 
 scalar_t__ MAC_IPG1 ; 
 scalar_t__ MAC_IPG2 ; 
 scalar_t__ MAC_JAMSIZE ; 
 scalar_t__ MAC_LCOLL ; 
 scalar_t__ MAC_LERR ; 
 scalar_t__ MAC_MAXFSZ ; 
 scalar_t__ MAC_MCCFG ; 
 scalar_t__ MAC_MCMASK ; 
 scalar_t__ MAC_MCTYPE ; 
 scalar_t__ MAC_MINFSZ ; 
 scalar_t__ MAC_NCOLL ; 
 scalar_t__ MAC_PASIZE ; 
 scalar_t__ MAC_PATMPS ; 
 scalar_t__ MAC_RANDSEED ; 
 scalar_t__ MAC_RFCTR ; 
 scalar_t__ MAC_RXCFG ; 
 int MAC_RXCFG_SFCS ; 
 scalar_t__ MAC_RXCVERR ; 
 scalar_t__ MAC_RXMASK ; 
 int MAC_RXSTAT_RCV ; 
 scalar_t__ MAC_SNDPAUSE ; 
 scalar_t__ MAC_STIME ; 
 scalar_t__ MAC_TXCFG ; 
 scalar_t__ MAC_TXMASK ; 
 int MAC_TXSTAT_XMIT ; 
 scalar_t__ MAC_XIFCFG ; 
 scalar_t__ WOL_WAKECSR ; 
 int gem_setup_multicast (struct gem*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_init_mac(struct gem *gp)
{
	unsigned char *e = &gp->dev->dev_addr[0];

	writel(0x1bf0, gp->regs + MAC_SNDPAUSE);

	writel(0x00, gp->regs + MAC_IPG0);
	writel(0x08, gp->regs + MAC_IPG1);
	writel(0x04, gp->regs + MAC_IPG2);
	writel(0x40, gp->regs + MAC_STIME);
	writel(0x40, gp->regs + MAC_MINFSZ);

	/* Ethernet payload + header + FCS + optional VLAN tag. */
	writel(0x20000000 | (gp->rx_buf_sz + 4), gp->regs + MAC_MAXFSZ);

	writel(0x07, gp->regs + MAC_PASIZE);
	writel(0x04, gp->regs + MAC_JAMSIZE);
	writel(0x10, gp->regs + MAC_ATTLIM);
	writel(0x8808, gp->regs + MAC_MCTYPE);

	writel((e[5] | (e[4] << 8)) & 0x3ff, gp->regs + MAC_RANDSEED);

	writel((e[4] << 8) | e[5], gp->regs + MAC_ADDR0);
	writel((e[2] << 8) | e[3], gp->regs + MAC_ADDR1);
	writel((e[0] << 8) | e[1], gp->regs + MAC_ADDR2);

	writel(0, gp->regs + MAC_ADDR3);
	writel(0, gp->regs + MAC_ADDR4);
	writel(0, gp->regs + MAC_ADDR5);

	writel(0x0001, gp->regs + MAC_ADDR6);
	writel(0xc200, gp->regs + MAC_ADDR7);
	writel(0x0180, gp->regs + MAC_ADDR8);

	writel(0, gp->regs + MAC_AFILT0);
	writel(0, gp->regs + MAC_AFILT1);
	writel(0, gp->regs + MAC_AFILT2);
	writel(0, gp->regs + MAC_AF21MSK);
	writel(0, gp->regs + MAC_AF0MSK);

	gp->mac_rx_cfg = gem_setup_multicast(gp);
#ifdef STRIP_FCS
	gp->mac_rx_cfg |= MAC_RXCFG_SFCS;
#endif
	writel(0, gp->regs + MAC_NCOLL);
	writel(0, gp->regs + MAC_FASUCC);
	writel(0, gp->regs + MAC_ECOLL);
	writel(0, gp->regs + MAC_LCOLL);
	writel(0, gp->regs + MAC_DTIMER);
	writel(0, gp->regs + MAC_PATMPS);
	writel(0, gp->regs + MAC_RFCTR);
	writel(0, gp->regs + MAC_LERR);
	writel(0, gp->regs + MAC_AERR);
	writel(0, gp->regs + MAC_FCSERR);
	writel(0, gp->regs + MAC_RXCVERR);

	/* Clear RX/TX/MAC/XIF config, we will set these up and enable
	 * them once a link is established.
	 */
	writel(0, gp->regs + MAC_TXCFG);
	writel(gp->mac_rx_cfg, gp->regs + MAC_RXCFG);
	writel(0, gp->regs + MAC_MCCFG);
	writel(0, gp->regs + MAC_XIFCFG);

	/* Setup MAC interrupts.  We want to get all of the interesting
	 * counter expiration events, but we do not want to hear about
	 * normal rx/tx as the DMA engine tells us that.
	 */
	writel(MAC_TXSTAT_XMIT, gp->regs + MAC_TXMASK);
	writel(MAC_RXSTAT_RCV, gp->regs + MAC_RXMASK);

	/* Don't enable even the PAUSE interrupts for now, we
	 * make no use of those events other than to record them.
	 */
	writel(0xffffffff, gp->regs + MAC_MCMASK);

	/* Don't enable GEM's WOL in normal operations
	 */
	if (gp->has_wol)
		writel(0, gp->regs + WOL_WAKECSR);
}