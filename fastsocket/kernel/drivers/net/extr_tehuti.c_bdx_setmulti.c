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
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int flags; scalar_t__ mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int* dmi_addr; struct dev_mc_list* next; } ;
struct bdx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,scalar_t__) ; 
 int /*<<< orphan*/  ENTER ; 
 int ETH_ALEN ; 
 int GMAC_RX_FILTER_AB ; 
 int GMAC_RX_FILTER_AM ; 
 int GMAC_RX_FILTER_OSEN ; 
 int GMAC_RX_FILTER_PRM ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MAC_MCST_HASH_NUM ; 
 int MAC_MCST_NUM ; 
 int READ_REG (struct bdx_priv*,int) ; 
 int /*<<< orphan*/  RET () ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int,int) ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 
 int regGMAC_RXF_A ; 
 int regRX_MAC_MCST0 ; 
 int regRX_MAC_MCST1 ; 
 int regRX_MCST_HASH0 ; 

__attribute__((used)) static void bdx_setmulti(struct net_device *ndev)
{
	struct bdx_priv *priv = netdev_priv(ndev);

	u32 rxf_val =
	    GMAC_RX_FILTER_AM | GMAC_RX_FILTER_AB | GMAC_RX_FILTER_OSEN;
	int i;

	ENTER;
	/* IMF - imperfect (hash) rx multicat filter */
	/* PMF - perfect rx multicat filter */

	/* FIXME: RXE(OFF) */
	if (ndev->flags & IFF_PROMISC) {
		rxf_val |= GMAC_RX_FILTER_PRM;
	} else if (ndev->flags & IFF_ALLMULTI) {
		/* set IMF to accept all multicast frmaes */
		for (i = 0; i < MAC_MCST_HASH_NUM; i++)
			WRITE_REG(priv, regRX_MCST_HASH0 + i * 4, ~0);
	} else if (ndev->mc_count) {
		u8 hash;
		struct dev_mc_list *mclist;
		u32 reg, val;

		/* set IMF to deny all multicast frames */
		for (i = 0; i < MAC_MCST_HASH_NUM; i++)
			WRITE_REG(priv, regRX_MCST_HASH0 + i * 4, 0);
		/* set PMF to deny all multicast frames */
		for (i = 0; i < MAC_MCST_NUM; i++) {
			WRITE_REG(priv, regRX_MAC_MCST0 + i * 8, 0);
			WRITE_REG(priv, regRX_MAC_MCST1 + i * 8, 0);
		}

		/* use PMF to accept first MAC_MCST_NUM (15) addresses */
		/* TBD: sort addreses and write them in ascending order
		 * into RX_MAC_MCST regs. we skip this phase now and accept ALL
		 * multicast frames throu IMF */
		mclist = ndev->mc_list;

		/* accept the rest of addresses throu IMF */
		for (; mclist; mclist = mclist->next) {
			hash = 0;
			for (i = 0; i < ETH_ALEN; i++)
				hash ^= mclist->dmi_addr[i];
			reg = regRX_MCST_HASH0 + ((hash >> 5) << 2);
			val = READ_REG(priv, reg);
			val |= (1 << (hash % 32));
			WRITE_REG(priv, reg, val);
		}

	} else {
		DBG("only own mac %d\n", ndev->mc_count);
		rxf_val |= GMAC_RX_FILTER_AB;
	}
	WRITE_REG(priv, regGMAC_RXF_A, rxf_val);
	/* enable RX */
	/* FIXME: RXE(ON) */
	RET();
}