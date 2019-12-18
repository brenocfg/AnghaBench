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
struct pnp_dev {scalar_t__ status; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ PNP_ATTACHED ; 
 scalar_t__ PNP_READY ; 
 int /*<<< orphan*/  pnp_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int pnp_device_attach(struct pnp_dev *pnp_dev)
{
	spin_lock(&pnp_lock);
	if (pnp_dev->status != PNP_READY) {
		spin_unlock(&pnp_lock);
		return -EBUSY;
	}
	pnp_dev->status = PNP_ATTACHED;
	spin_unlock(&pnp_lock);
	return 0;
}