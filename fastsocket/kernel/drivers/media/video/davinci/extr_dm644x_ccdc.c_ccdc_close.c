#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_3__ {int fp_num; scalar_t__ fpc_table_addr; } ;
struct ccdc_config_params_raw {TYPE_1__ fault_pxl; } ;
struct TYPE_4__ {struct ccdc_config_params_raw config_params; } ;

/* Variables and functions */
 int FP_NUM_BYTES ; 
 TYPE_2__ ccdc_hw_params_raw ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 scalar_t__ phys_to_virt (unsigned long) ; 

__attribute__((used)) static int ccdc_close(struct device *dev)
{
	struct ccdc_config_params_raw *config_params =
		&ccdc_hw_params_raw.config_params;
	unsigned int *fpc_physaddr = NULL, *fpc_virtaddr = NULL;

	fpc_physaddr = (unsigned int *)config_params->fault_pxl.fpc_table_addr;

	if (fpc_physaddr != NULL) {
		fpc_virtaddr = (unsigned int *)
		    phys_to_virt((unsigned long)fpc_physaddr);
		free_pages((unsigned long)fpc_virtaddr,
			   get_order(config_params->fault_pxl.fp_num *
			   FP_NUM_BYTES));
	}
	return 0;
}