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
typedef  int /*<<< orphan*/  u16 ;
struct protection_domain {int dev_cnt; int /*<<< orphan*/  lock; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_dte_entry (int /*<<< orphan*/ ,struct protection_domain*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __attach_device(struct amd_iommu *iommu,
			    struct protection_domain *domain,
			    u16 devid)
{
	/* lock domain */
	spin_lock(&domain->lock);

	/* update DTE entry */
	set_dte_entry(devid, domain);

	domain->dev_cnt += 1;

	/* ready */
	spin_unlock(&domain->lock);
}