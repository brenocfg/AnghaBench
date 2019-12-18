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
struct mdio_ops {int dummy; } ;
struct cphy {scalar_t__ bmsr; int /*<<< orphan*/  phy_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,struct net_device*,int,int /*<<< orphan*/ *,struct mdio_ops const*) ; 
 struct cphy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my3126_ops ; 
 int /*<<< orphan*/  my3216_poll ; 

__attribute__((used)) static struct cphy *my3126_phy_create(struct net_device *dev,
			int phy_addr, const struct mdio_ops *mdio_ops)
{
	struct cphy *cphy = kzalloc(sizeof (*cphy), GFP_KERNEL);

	if (!cphy)
		return NULL;

	cphy_init(cphy, dev, phy_addr, &my3126_ops, mdio_ops);
	INIT_DELAYED_WORK(&cphy->phy_update, my3216_poll);
	cphy->bmsr = 0;

	return cphy;
}