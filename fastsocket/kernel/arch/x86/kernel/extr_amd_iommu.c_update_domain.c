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
struct protection_domain {int updated; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_devices_by_domain (struct protection_domain*) ; 
 int /*<<< orphan*/  iommu_flush_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_device_table (struct protection_domain*) ; 

__attribute__((used)) static void update_domain(struct protection_domain *domain)
{
	if (!domain->updated)
		return;

	update_device_table(domain);
	flush_devices_by_domain(domain);
	iommu_flush_domain(domain->id);

	domain->updated = false;
}