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
struct aem_ipmi_data {int /*<<< orphan*/  bmc_device; } ;

/* Variables and functions */
 int aem_find_aem1_count (struct aem_ipmi_data*) ; 
 int aem_init_aem1_inst (struct aem_ipmi_data*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int aem_init_aem1(struct aem_ipmi_data *probe)
{
	int num, i, err;

	num = aem_find_aem1_count(probe);
	for (i = 0; i < num; i++) {
		err = aem_init_aem1_inst(probe, i);
		if (err) {
			dev_err(probe->bmc_device,
				"Error %d initializing AEM1 0x%X\n",
				err, i);
			return err;
		}
	}

	return 0;
}