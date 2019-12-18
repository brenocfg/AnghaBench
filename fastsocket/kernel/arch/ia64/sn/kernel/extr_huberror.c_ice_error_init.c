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
struct hubdev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SGI_TIO_ERROR ; 
 scalar_t__ hub_eint_handler ; 
 int /*<<< orphan*/  printk (char*,struct hubdev_info*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  sn_set_err_irq_affinity (int /*<<< orphan*/ ) ; 

void ice_error_init(struct hubdev_info *hubdev_info)
{

        if (request_irq
            (SGI_TIO_ERROR, (void *)hub_eint_handler, IRQF_SHARED, "SN_TIO_error",
             (void *)hubdev_info)) {
                printk("ice_error_init: request_irq() error hubdev_info 0x%p\n",
                       hubdev_info);
		return;
	}
	sn_set_err_irq_affinity(SGI_TIO_ERROR);
}