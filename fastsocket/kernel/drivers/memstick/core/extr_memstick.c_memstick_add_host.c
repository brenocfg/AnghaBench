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
struct memstick_host {int /*<<< orphan*/  (* set_param ) (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEMSTICK_POWER ; 
 int /*<<< orphan*/  MEMSTICK_POWER_OFF ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int idr_get_new (int /*<<< orphan*/ *,struct memstick_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memstick_detect_change (struct memstick_host*) ; 
 int /*<<< orphan*/  memstick_host_idr ; 
 int /*<<< orphan*/  memstick_host_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct memstick_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int memstick_add_host(struct memstick_host *host)
{
	int rc;

	if (!idr_pre_get(&memstick_host_idr, GFP_KERNEL))
		return -ENOMEM;

	spin_lock(&memstick_host_lock);
	rc = idr_get_new(&memstick_host_idr, host, &host->id);
	spin_unlock(&memstick_host_lock);
	if (rc)
		return rc;

	dev_set_name(&host->dev, "memstick%u", host->id);

	rc = device_add(&host->dev);
	if (rc) {
		spin_lock(&memstick_host_lock);
		idr_remove(&memstick_host_idr, host->id);
		spin_unlock(&memstick_host_lock);
		return rc;
	}

	host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_OFF);
	memstick_detect_change(host);
	return 0;
}