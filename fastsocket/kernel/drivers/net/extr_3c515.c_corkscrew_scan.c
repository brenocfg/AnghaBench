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
struct pnp_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct corkscrew_private {int dummy; } ;
struct TYPE_2__ {scalar_t__ vendor; scalar_t__ driver_data; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  check_device (int) ; 
 int /*<<< orphan*/  cleanup_card (struct net_device*) ; 
 scalar_t__ corkscrew_debug ; 
 TYPE_1__* corkscrew_isapnp_adapters ; 
 int corkscrew_setup (struct net_device*,int,struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  inl (int) ; 
 int /*<<< orphan*/  inw (int) ; 
 int /*<<< orphan*/  netdev_boot_setup_check (struct net_device*) ; 
 int nopnp ; 
 scalar_t__ pnp_activate_dev (struct pnp_dev*) ; 
 scalar_t__ pnp_device_attach (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_device_detach (struct pnp_dev*) ; 
 struct pnp_dev* pnp_find_dev (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct pnp_dev*) ; 
 int pnp_irq (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_irq_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int pnp_port_start (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_port_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct net_device *corkscrew_scan(int unit)
{
	struct net_device *dev;
	static int cards_found = 0;
	static int ioaddr;
	int err;
#ifdef __ISAPNP__
	short i;
	static int pnp_cards;
#endif

	dev = alloc_etherdev(sizeof(struct corkscrew_private));
	if (!dev)
		return ERR_PTR(-ENOMEM);

	if (unit >= 0) {
		sprintf(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
	}

#ifdef __ISAPNP__
	if(nopnp == 1)
		goto no_pnp;
	for(i=0; corkscrew_isapnp_adapters[i].vendor != 0; i++) {
		struct pnp_dev *idev = NULL;
		int irq;
		while((idev = pnp_find_dev(NULL,
					   corkscrew_isapnp_adapters[i].vendor,
					   corkscrew_isapnp_adapters[i].function,
					   idev))) {

			if (pnp_device_attach(idev) < 0)
				continue;
			if (pnp_activate_dev(idev) < 0) {
				pr_warning("pnp activate failed (out of resources?)\n");
				pnp_device_detach(idev);
				continue;
			}
			if (!pnp_port_valid(idev, 0) || !pnp_irq_valid(idev, 0)) {
				pnp_device_detach(idev);
				continue;
			}
			ioaddr = pnp_port_start(idev, 0);
			irq = pnp_irq(idev, 0);
			if (!check_device(ioaddr)) {
				pnp_device_detach(idev);
				continue;
			}
			if(corkscrew_debug)
				pr_debug("ISAPNP reports %s at i/o 0x%x, irq %d\n",
					(char*) corkscrew_isapnp_adapters[i].driver_data, ioaddr, irq);
			pr_info("3c515 Resource configuration register %#4.4x, DCR %4.4x.\n",
		     		inl(ioaddr + 0x2002), inw(ioaddr + 0x2000));
			/* irq = inw(ioaddr + 0x2002) & 15; */ /* Use the irq from isapnp */
			SET_NETDEV_DEV(dev, &idev->dev);
			pnp_cards++;
			err = corkscrew_setup(dev, ioaddr, idev, cards_found++);
			if (!err)
				return dev;
			cleanup_card(dev);
		}
	}
no_pnp:
#endif /* __ISAPNP__ */

	/* Check all locations on the ISA bus -- evil! */
	for (ioaddr = 0x100; ioaddr < 0x400; ioaddr += 0x20) {
		if (!check_device(ioaddr))
			continue;

		pr_info("3c515 Resource configuration register %#4.4x, DCR %4.4x.\n",
		     inl(ioaddr + 0x2002), inw(ioaddr + 0x2000));
		err = corkscrew_setup(dev, ioaddr, NULL, cards_found++);
		if (!err)
			return dev;
		cleanup_card(dev);
	}
	free_netdev(dev);
	return NULL;
}