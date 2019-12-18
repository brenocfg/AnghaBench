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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sky2_port {unsigned int port; struct sky2_hw* hw; } ;
struct sky2_hw {scalar_t__ chip_id; int flags; int /*<<< orphan*/  napi; TYPE_1__* pdev; } ;
struct net_device {int mtu; int /*<<< orphan*/  trans_start; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  B0_Y2_SP_LISR ; 
 scalar_t__ CHIP_ID_YUKON_FE ; 
 scalar_t__ CHIP_ID_YUKON_FE_P ; 
 int /*<<< orphan*/  DATA_BLIND_DEF ; 
 int DATA_BLIND_VAL (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ETH_DATA_LEN ; 
 int ETH_JUMBO_MTU ; 
 int ETH_ZLEN ; 
 int GM_GPCR_RX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  GM_SERIAL_MODE ; 
 int GM_SMOD_JUMBO_ENA ; 
 int GM_SMOD_VLAN_ENA ; 
 int /*<<< orphan*/  IPG_DATA_DEF ; 
 int IPG_DATA_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int /*<<< orphan*/  RB_ENA_OP_MD ; 
 int SKY2_HW_RAM_BUFFER ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int gma_read16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/ * rxqaddr ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_rx_clean (struct sky2_port*) ; 
 int sky2_rx_start (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_rx_stop (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_set_tx_stfwd (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_change_mtu(struct net_device *dev, int new_mtu)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	int err;
	u16 ctl, mode;
	u32 imask;

	if (new_mtu < ETH_ZLEN || new_mtu > ETH_JUMBO_MTU)
		return -EINVAL;

	if (new_mtu > ETH_DATA_LEN &&
	    (hw->chip_id == CHIP_ID_YUKON_FE ||
	     hw->chip_id == CHIP_ID_YUKON_FE_P))
		return -EINVAL;

	if (!netif_running(dev)) {
		dev->mtu = new_mtu;
		return 0;
	}

	imask = sky2_read32(hw, B0_IMSK);
	sky2_write32(hw, B0_IMSK, 0);

	dev->trans_start = jiffies;	/* prevent tx timeout */
	netif_stop_queue(dev);
	napi_disable(&hw->napi);

	synchronize_irq(hw->pdev->irq);

	if (!(hw->flags & SKY2_HW_RAM_BUFFER))
		sky2_set_tx_stfwd(hw, port);

	ctl = gma_read16(hw, port, GM_GP_CTRL);
	gma_write16(hw, port, GM_GP_CTRL, ctl & ~GM_GPCR_RX_ENA);
	sky2_rx_stop(sky2);
	sky2_rx_clean(sky2);

	dev->mtu = new_mtu;

	mode = DATA_BLIND_VAL(DATA_BLIND_DEF) |
		GM_SMOD_VLAN_ENA | IPG_DATA_VAL(IPG_DATA_DEF);

	if (dev->mtu > ETH_DATA_LEN)
		mode |= GM_SMOD_JUMBO_ENA;

	gma_write16(hw, port, GM_SERIAL_MODE, mode);

	sky2_write8(hw, RB_ADDR(rxqaddr[port], RB_CTRL), RB_ENA_OP_MD);

	err = sky2_rx_start(sky2);
	sky2_write32(hw, B0_IMSK, imask);

	sky2_read32(hw, B0_Y2_SP_LISR);
	napi_enable(&hw->napi);

	if (err)
		dev_close(dev);
	else {
		gma_write16(hw, port, GM_GP_CTRL, ctl);

		netif_wake_queue(dev);
	}

	return err;
}