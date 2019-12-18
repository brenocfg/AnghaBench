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
struct device {int dummy; } ;
struct aem_ipmi_data {int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  aem_init_aem1 (struct aem_ipmi_data*) ; 
 int /*<<< orphan*/  aem_init_aem2 (struct aem_ipmi_data*) ; 
 scalar_t__ aem_init_ipmi_data (struct aem_ipmi_data*,int,struct device*) ; 
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aem_register_bmc(int iface, struct device *dev)
{
	struct aem_ipmi_data probe;

	if (aem_init_ipmi_data(&probe, iface, dev))
		return;

	/* Ignore probe errors; they won't cause problems */
	aem_init_aem1(&probe);
	aem_init_aem2(&probe);

	ipmi_destroy_user(probe.user);
}