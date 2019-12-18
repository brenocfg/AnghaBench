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
struct tifm_adapter {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int idr_get_new (int /*<<< orphan*/ *,struct tifm_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tifm_adapter_idr ; 
 int /*<<< orphan*/  tifm_adapter_lock ; 

int tifm_add_adapter(struct tifm_adapter *fm)
{
	int rc;

	if (!idr_pre_get(&tifm_adapter_idr, GFP_KERNEL))
		return -ENOMEM;

	spin_lock(&tifm_adapter_lock);
	rc = idr_get_new(&tifm_adapter_idr, fm, &fm->id);
	spin_unlock(&tifm_adapter_lock);
	if (rc)
		return rc;

	dev_set_name(&fm->dev, "tifm%u", fm->id);
	rc = device_add(&fm->dev);
	if (rc) {
		spin_lock(&tifm_adapter_lock);
		idr_remove(&tifm_adapter_idr, fm->id);
		spin_unlock(&tifm_adapter_lock);
	}

	return rc;
}