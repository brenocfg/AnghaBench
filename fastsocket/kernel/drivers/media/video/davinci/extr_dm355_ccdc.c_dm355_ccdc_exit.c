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

/* Variables and functions */
 int /*<<< orphan*/  ccdc_hw_dev ; 
 int /*<<< orphan*/  vpfe_unregister_ccdc_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dm355_ccdc_exit(void)
{
	vpfe_unregister_ccdc_device(&ccdc_hw_dev);
}