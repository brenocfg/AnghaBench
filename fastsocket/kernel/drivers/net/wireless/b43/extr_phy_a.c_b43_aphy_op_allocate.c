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
struct TYPE_2__ {struct b43_phy_a* a; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_a {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int b43_aphy_init_tssi2dbm_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  kfree (struct b43_phy_a*) ; 
 struct b43_phy_a* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b43_aphy_op_allocate(struct b43_wldev *dev)
{
	struct b43_phy_a *aphy;
	int err;

	aphy = kzalloc(sizeof(*aphy), GFP_KERNEL);
	if (!aphy)
		return -ENOMEM;
	dev->phy.a = aphy;

	err = b43_aphy_init_tssi2dbm_table(dev);
	if (err)
		goto err_free_aphy;

	return 0;

err_free_aphy:
	kfree(aphy);
	dev->phy.a = NULL;

	return err;
}