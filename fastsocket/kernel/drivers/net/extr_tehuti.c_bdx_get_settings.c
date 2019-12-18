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
struct rxf_desc {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int supported; int advertising; int maxtxpkt; int maxrxpkt; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct bdx_priv {int /*<<< orphan*/  tdintcm; int /*<<< orphan*/  rdintcm; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int BDX_TXF_DESC_SZ ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int GET_PCK_TH (int /*<<< orphan*/ ) ; 
 int PCK_TH_MULT ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bdx_get_settings(struct net_device *netdev, struct ethtool_cmd *ecmd)
{
	u32 rdintcm;
	u32 tdintcm;
	struct bdx_priv *priv = netdev_priv(netdev);

	rdintcm = priv->rdintcm;
	tdintcm = priv->tdintcm;

	ecmd->supported = (SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE);
	ecmd->advertising = (ADVERTISED_10000baseT_Full | ADVERTISED_FIBRE);
	ecmd->speed = SPEED_10000;
	ecmd->duplex = DUPLEX_FULL;
	ecmd->port = PORT_FIBRE;
	ecmd->transceiver = XCVR_EXTERNAL;	/* what does it mean? */
	ecmd->autoneg = AUTONEG_DISABLE;

	/* PCK_TH measures in multiples of FIFO bytes
	   We translate to packets */
	ecmd->maxtxpkt =
	    ((GET_PCK_TH(tdintcm) * PCK_TH_MULT) / BDX_TXF_DESC_SZ);
	ecmd->maxrxpkt =
	    ((GET_PCK_TH(rdintcm) * PCK_TH_MULT) / sizeof(struct rxf_desc));

	return 0;
}