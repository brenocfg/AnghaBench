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
struct TYPE_4__ {int giga; scalar_t__ full; } ;
struct s6gmac {scalar_t__ reg; TYPE_2__ link; TYPE_1__* phydev; } ;
struct net_device {int flags; int mtu; int* dev_addr; } ;
struct TYPE_3__ {int supported; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int IFF_LOOPBACK ; 
 scalar_t__ S6_GMAC_FIFOCONF0 ; 
 int S6_GMAC_FIFOCONF0_FRFENREQ ; 
 int S6_GMAC_FIFOCONF0_FTFENREQ ; 
 int S6_GMAC_FIFOCONF0_SRFENREQ ; 
 int S6_GMAC_FIFOCONF0_STFENREQ ; 
 int S6_GMAC_FIFOCONF0_WTMENREQ ; 
 scalar_t__ S6_GMAC_FIFOCONF3 ; 
 int S6_GMAC_FIFOCONF3_CFGFTTH ; 
 int S6_GMAC_FIFOCONF3_CFGHWMFT ; 
 scalar_t__ S6_GMAC_FIFOCONF4 ; 
 scalar_t__ S6_GMAC_FIFOCONF5 ; 
 int S6_GMAC_FIFOCONF5_CFGBYTM ; 
 int S6_GMAC_FIFOCONF5_DROPLT64 ; 
 int S6_GMAC_FIFOCONF5_RXDROPSIZE ; 
 int S6_GMAC_FIFOCONF_RSV_CRCERR ; 
 int S6_GMAC_FIFOCONF_RSV_CTRLFRAME ; 
 int S6_GMAC_FIFOCONF_RSV_DRIBBLE ; 
 int S6_GMAC_FIFOCONF_RSV_MASK ; 
 int S6_GMAC_FIFOCONF_RSV_OK ; 
 int S6_GMAC_FIFOCONF_RSV_PAUSECTRL ; 
 int S6_GMAC_FIFOCONF_RSV_RUNT ; 
 int S6_GMAC_FIFOCONF_RSV_TRUNCATED ; 
 int S6_GMAC_FIFOCONF_RSV_UNOPCODE ; 
 scalar_t__ S6_GMAC_HOST_PBLKCTRL ; 
 int S6_GMAC_HOST_PBLKCTRL_RGMII ; 
 int S6_GMAC_HOST_PBLKCTRL_RXBSIZ ; 
 int S6_GMAC_HOST_PBLKCTRL_RXENA ; 
 int S6_GMAC_HOST_PBLKCTRL_RXSRES ; 
 int S6_GMAC_HOST_PBLKCTRL_SIZ_128 ; 
 int S6_GMAC_HOST_PBLKCTRL_STATCLEAR ; 
 int S6_GMAC_HOST_PBLKCTRL_STATENA ; 
 int S6_GMAC_HOST_PBLKCTRL_TXBSIZ ; 
 int S6_GMAC_HOST_PBLKCTRL_TXENA ; 
 int S6_GMAC_HOST_PBLKCTRL_TXSRES ; 
 scalar_t__ S6_GMAC_MACCONF1 ; 
 int S6_GMAC_MACCONF1_LOOPBACK ; 
 int S6_GMAC_MACCONF1_RESRXFUNC ; 
 int S6_GMAC_MACCONF1_RESRXMACCTRL ; 
 int S6_GMAC_MACCONF1_RESTXFUNC ; 
 int S6_GMAC_MACCONF1_RESTXMACCTRL ; 
 int S6_GMAC_MACCONF1_RXENA ; 
 int S6_GMAC_MACCONF1_RXFLOWCTRL ; 
 int S6_GMAC_MACCONF1_SOFTRES ; 
 int S6_GMAC_MACCONF1_SYNCRX ; 
 int S6_GMAC_MACCONF1_SYNCTX ; 
 int S6_GMAC_MACCONF1_TXENA ; 
 int S6_GMAC_MACCONF1_TXFLOWCTRL ; 
 scalar_t__ S6_GMAC_MACCONF2 ; 
 int S6_GMAC_MACCONF2_FULL ; 
 int S6_GMAC_MACCONF2_IFMODE ; 
 int S6_GMAC_MACCONF2_IFMODE_BYTE ; 
 int S6_GMAC_MACCONF2_IFMODE_NIBBLE ; 
 int S6_GMAC_MACCONF2_LENGTHFCHK ; 
 int S6_GMAC_MACCONF2_PADCRCENA ; 
 int S6_GMAC_MACCONF2_PREAMBLELEN ; 
 scalar_t__ S6_GMAC_MACMAXFRAMELEN ; 
 scalar_t__ S6_GMAC_MACSTATADDR1 ; 
 scalar_t__ S6_GMAC_MACSTATADDR2 ; 
 int S6_MAX_FRLEN ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 struct s6gmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  s6gmac_set_dstaddr (struct s6gmac*,int,int,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void s6gmac_init_device(struct net_device *dev)
{
	struct s6gmac *pd = netdev_priv(dev);
	int is_rgmii = !!(pd->phydev->supported
		& (SUPPORTED_1000baseT_Full | SUPPORTED_1000baseT_Half));
#if 0
	writel(1 << S6_GMAC_MACCONF1_SYNCTX |
		1 << S6_GMAC_MACCONF1_SYNCRX |
		1 << S6_GMAC_MACCONF1_TXFLOWCTRL |
		1 << S6_GMAC_MACCONF1_RXFLOWCTRL |
		1 << S6_GMAC_MACCONF1_RESTXFUNC |
		1 << S6_GMAC_MACCONF1_RESRXFUNC |
		1 << S6_GMAC_MACCONF1_RESTXMACCTRL |
		1 << S6_GMAC_MACCONF1_RESRXMACCTRL,
		pd->reg + S6_GMAC_MACCONF1);
#endif
	writel(1 << S6_GMAC_MACCONF1_SOFTRES, pd->reg + S6_GMAC_MACCONF1);
	udelay(1000);
	writel(1 << S6_GMAC_MACCONF1_TXENA | 1 << S6_GMAC_MACCONF1_RXENA,
		pd->reg + S6_GMAC_MACCONF1);
	writel(1 << S6_GMAC_HOST_PBLKCTRL_TXSRES |
		1 << S6_GMAC_HOST_PBLKCTRL_RXSRES,
		pd->reg + S6_GMAC_HOST_PBLKCTRL);
	writel(S6_GMAC_HOST_PBLKCTRL_SIZ_128 << S6_GMAC_HOST_PBLKCTRL_TXBSIZ |
		S6_GMAC_HOST_PBLKCTRL_SIZ_128 << S6_GMAC_HOST_PBLKCTRL_RXBSIZ |
		1 << S6_GMAC_HOST_PBLKCTRL_STATENA |
		1 << S6_GMAC_HOST_PBLKCTRL_STATCLEAR |
		is_rgmii << S6_GMAC_HOST_PBLKCTRL_RGMII,
		pd->reg + S6_GMAC_HOST_PBLKCTRL);
	writel(1 << S6_GMAC_MACCONF1_TXENA |
		1 << S6_GMAC_MACCONF1_RXENA |
		(dev->flags & IFF_LOOPBACK ? 1 : 0)
			<< S6_GMAC_MACCONF1_LOOPBACK,
		pd->reg + S6_GMAC_MACCONF1);
	writel(dev->mtu && (dev->mtu < (S6_MAX_FRLEN - ETH_HLEN-ETH_FCS_LEN)) ?
			dev->mtu+ETH_HLEN+ETH_FCS_LEN : S6_MAX_FRLEN,
		pd->reg + S6_GMAC_MACMAXFRAMELEN);
	writel((pd->link.full ? 1 : 0) << S6_GMAC_MACCONF2_FULL |
		1 << S6_GMAC_MACCONF2_PADCRCENA |
		1 << S6_GMAC_MACCONF2_LENGTHFCHK |
		(pd->link.giga ?
			S6_GMAC_MACCONF2_IFMODE_BYTE :
			S6_GMAC_MACCONF2_IFMODE_NIBBLE)
			<< S6_GMAC_MACCONF2_IFMODE |
		7 << S6_GMAC_MACCONF2_PREAMBLELEN,
		pd->reg + S6_GMAC_MACCONF2);
	writel(0, pd->reg + S6_GMAC_MACSTATADDR1);
	writel(0, pd->reg + S6_GMAC_MACSTATADDR2);
	writel(1 << S6_GMAC_FIFOCONF0_WTMENREQ |
		1 << S6_GMAC_FIFOCONF0_SRFENREQ |
		1 << S6_GMAC_FIFOCONF0_FRFENREQ |
		1 << S6_GMAC_FIFOCONF0_STFENREQ |
		1 << S6_GMAC_FIFOCONF0_FTFENREQ,
		pd->reg + S6_GMAC_FIFOCONF0);
	writel(128 << S6_GMAC_FIFOCONF3_CFGFTTH |
		128 << S6_GMAC_FIFOCONF3_CFGHWMFT,
		pd->reg + S6_GMAC_FIFOCONF3);
	writel((S6_GMAC_FIFOCONF_RSV_MASK & ~(
			1 << S6_GMAC_FIFOCONF_RSV_RUNT |
			1 << S6_GMAC_FIFOCONF_RSV_CRCERR |
			1 << S6_GMAC_FIFOCONF_RSV_OK |
			1 << S6_GMAC_FIFOCONF_RSV_DRIBBLE |
			1 << S6_GMAC_FIFOCONF_RSV_CTRLFRAME |
			1 << S6_GMAC_FIFOCONF_RSV_PAUSECTRL |
			1 << S6_GMAC_FIFOCONF_RSV_UNOPCODE |
			1 << S6_GMAC_FIFOCONF_RSV_TRUNCATED)) |
		1 << S6_GMAC_FIFOCONF5_DROPLT64 |
		pd->link.giga << S6_GMAC_FIFOCONF5_CFGBYTM |
		1 << S6_GMAC_FIFOCONF5_RXDROPSIZE,
		pd->reg + S6_GMAC_FIFOCONF5);
	writel(1 << S6_GMAC_FIFOCONF_RSV_RUNT |
		1 << S6_GMAC_FIFOCONF_RSV_CRCERR |
		1 << S6_GMAC_FIFOCONF_RSV_DRIBBLE |
		1 << S6_GMAC_FIFOCONF_RSV_CTRLFRAME |
		1 << S6_GMAC_FIFOCONF_RSV_PAUSECTRL |
		1 << S6_GMAC_FIFOCONF_RSV_UNOPCODE |
		1 << S6_GMAC_FIFOCONF_RSV_TRUNCATED,
		pd->reg + S6_GMAC_FIFOCONF4);
	s6gmac_set_dstaddr(pd, 0,
		0xFFFFFFFF, 0x0000FFFF, 0xFFFFFFFF, 0x0000FFFF);
	s6gmac_set_dstaddr(pd, 1,
		dev->dev_addr[5] |
		dev->dev_addr[4] << 8 |
		dev->dev_addr[3] << 16 |
		dev->dev_addr[2] << 24,
		dev->dev_addr[1] |
		dev->dev_addr[0] << 8,
		0xFFFFFFFF, 0x0000FFFF);
	s6gmac_set_dstaddr(pd, 2,
		0x00000000, 0x00000100, 0x00000000, 0x00000100);
	s6gmac_set_dstaddr(pd, 3,
		0x00000000, 0x00000000, 0x00000000, 0x00000000);
	writel(1 << S6_GMAC_HOST_PBLKCTRL_TXENA |
		1 << S6_GMAC_HOST_PBLKCTRL_RXENA |
		S6_GMAC_HOST_PBLKCTRL_SIZ_128 << S6_GMAC_HOST_PBLKCTRL_TXBSIZ |
		S6_GMAC_HOST_PBLKCTRL_SIZ_128 << S6_GMAC_HOST_PBLKCTRL_RXBSIZ |
		1 << S6_GMAC_HOST_PBLKCTRL_STATENA |
		1 << S6_GMAC_HOST_PBLKCTRL_STATCLEAR |
		is_rgmii << S6_GMAC_HOST_PBLKCTRL_RGMII,
		pd->reg + S6_GMAC_HOST_PBLKCTRL);
}