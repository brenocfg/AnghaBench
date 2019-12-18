#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sh_eth_private {int post_rx; int post_fw; TYPE_1__* cd; int /*<<< orphan*/  ether_link_active_low; int /*<<< orphan*/  no_ether_link; int /*<<< orphan*/  edmac_endian; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  lock; } ;
struct sh_eth_plat_data {int /*<<< orphan*/  ether_link_active_low; int /*<<< orphan*/  no_ether_link; int /*<<< orphan*/  edmac_endian; int /*<<< orphan*/  phy; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_6__ {scalar_t__ platform_data; } ;
struct platform_device {int id; TYPE_3__ dev; } ;
struct net_device {int dma; int irq; int /*<<< orphan*/ * dev_addr; scalar_t__ base_addr; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* chip_reset ) (struct net_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int POST_FW ; 
 int POST_RX ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  SH_TSU_ADDR ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  read_mac_address (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 TYPE_1__ sh_eth_my_cpu_data ; 
 int /*<<< orphan*/  sh_eth_netdev_ops ; 
 int /*<<< orphan*/  sh_eth_set_default_cpu_data (TYPE_1__*) ; 
 int /*<<< orphan*/  sh_eth_tsu_init (int /*<<< orphan*/ ) ; 
 int sh_mdio_init (struct net_device*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int sh_eth_drv_probe(struct platform_device *pdev)
{
	int ret, i, devno = 0;
	struct resource *res;
	struct net_device *ndev = NULL;
	struct sh_eth_private *mdp;
	struct sh_eth_plat_data *pd;

	/* get base addr */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (unlikely(res == NULL)) {
		dev_err(&pdev->dev, "invalid resource\n");
		ret = -EINVAL;
		goto out;
	}

	ndev = alloc_etherdev(sizeof(struct sh_eth_private));
	if (!ndev) {
		dev_err(&pdev->dev, "Could not allocate device.\n");
		ret = -ENOMEM;
		goto out;
	}

	/* The sh Ether-specific entries in the device structure. */
	ndev->base_addr = res->start;
	devno = pdev->id;
	if (devno < 0)
		devno = 0;

	ndev->dma = -1;
	ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		ret = -ENODEV;
		goto out_release;
	}
	ndev->irq = ret;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	/* Fill in the fields of the device structure with ethernet values. */
	ether_setup(ndev);

	mdp = netdev_priv(ndev);
	spin_lock_init(&mdp->lock);

	pd = (struct sh_eth_plat_data *)(pdev->dev.platform_data);
	/* get PHY ID */
	mdp->phy_id = pd->phy;
	/* EDMAC endian */
	mdp->edmac_endian = pd->edmac_endian;
	mdp->no_ether_link = pd->no_ether_link;
	mdp->ether_link_active_low = pd->ether_link_active_low;

	/* set cpu data */
	mdp->cd = &sh_eth_my_cpu_data;
	sh_eth_set_default_cpu_data(mdp->cd);

	/* set function */
	ndev->netdev_ops = &sh_eth_netdev_ops;
	ndev->watchdog_timeo = TX_TIMEOUT;

	mdp->post_rx = POST_RX >> (devno << 1);
	mdp->post_fw = POST_FW >> (devno << 1);

	/* read and set MAC address */
	read_mac_address(ndev);

	/* First device only init */
	if (!devno) {
		if (mdp->cd->chip_reset)
			mdp->cd->chip_reset(ndev);

#if defined(SH_ETH_HAS_TSU)
		/* TSU init (Init only)*/
		sh_eth_tsu_init(SH_TSU_ADDR);
#endif
	}

	/* network device register */
	ret = register_netdev(ndev);
	if (ret)
		goto out_release;

	/* mdio bus init */
	ret = sh_mdio_init(ndev, pdev->id);
	if (ret)
		goto out_unregister;

	/* pritnt device infomation */
	pr_info("Base address at 0x%x, ",
	       (u32)ndev->base_addr);

	for (i = 0; i < 5; i++)
		printk("%02X:", ndev->dev_addr[i]);
	printk("%02X, IRQ %d.\n", ndev->dev_addr[i], ndev->irq);

	platform_set_drvdata(pdev, ndev);

	return ret;

out_unregister:
	unregister_netdev(ndev);

out_release:
	/* net_dev free */
	if (ndev)
		free_netdev(ndev);

out:
	return ret;
}