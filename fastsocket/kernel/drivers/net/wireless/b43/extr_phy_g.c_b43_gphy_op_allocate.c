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
struct TYPE_2__ {struct b43_txpower_lo_control* g; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_txpower_lo_control {struct b43_txpower_lo_control* lo_control; } ;
struct b43_phy_g {struct b43_phy_g* lo_control; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int b43_gphy_init_tssi2dbm_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  kfree (struct b43_txpower_lo_control*) ; 
 struct b43_txpower_lo_control* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b43_gphy_op_allocate(struct b43_wldev *dev)
{
	struct b43_phy_g *gphy;
	struct b43_txpower_lo_control *lo;
	int err;

	gphy = kzalloc(sizeof(*gphy), GFP_KERNEL);
	if (!gphy) {
		err = -ENOMEM;
		goto error;
	}
	dev->phy.g = gphy;

	lo = kzalloc(sizeof(*lo), GFP_KERNEL);
	if (!lo) {
		err = -ENOMEM;
		goto err_free_gphy;
	}
	gphy->lo_control = lo;

	err = b43_gphy_init_tssi2dbm_table(dev);
	if (err)
		goto err_free_lo;

	return 0;

err_free_lo:
	kfree(lo);
err_free_gphy:
	kfree(gphy);
error:
	return err;
}