#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * class; } ;
struct wpan_phy {TYPE_1__ dev; scalar_t__ idx; int /*<<< orphan*/  pib_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct wpan_phy*) ; 
 struct wpan_phy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wpan_phy_class ; 
 int /*<<< orphan*/  wpan_phy_idx ; 
 int /*<<< orphan*/  wpan_phy_idx_valid (scalar_t__) ; 
 int /*<<< orphan*/  wpan_phy_mutex ; 

struct wpan_phy *wpan_phy_alloc(size_t priv_size)
{
	struct wpan_phy *phy = kzalloc(sizeof(*phy) + priv_size,
			GFP_KERNEL);

	mutex_lock(&wpan_phy_mutex);
	phy->idx = wpan_phy_idx++;
	if (unlikely(!wpan_phy_idx_valid(phy->idx))) {
		wpan_phy_idx--;
		mutex_unlock(&wpan_phy_mutex);
		kfree(phy);
		return NULL;
	}
	mutex_unlock(&wpan_phy_mutex);

	mutex_init(&phy->pib_lock);

	device_initialize(&phy->dev);
	dev_set_name(&phy->dev, "wpan-phy%d", phy->idx);

	phy->dev.class = &wpan_phy_class;

	return phy;
}