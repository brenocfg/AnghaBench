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
struct sas_phy_data {struct sas_phy* phy; int /*<<< orphan*/  enable_work; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  event_lock; } ;
struct sas_phy {struct sas_phy_data* hostdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_SAS_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sas_phy_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_enable_work ; 
 int /*<<< orphan*/  phy_reset_work ; 

__attribute__((used)) static int sas_phy_setup(struct sas_phy *phy)
{
	struct sas_phy_data *d = kzalloc(sizeof(*d), GFP_KERNEL);

	if (!d)
		return -ENOMEM;

	mutex_init(&d->event_lock);
	INIT_SAS_WORK(&d->reset_work, phy_reset_work);
	INIT_SAS_WORK(&d->enable_work, phy_enable_work);
	d->phy = phy;
	phy->hostdata = d;

	return 0;
}