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
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  tsi_eth_driver ; 

__attribute__((used)) static int tsi108_ether_init(void)
{
	int ret;
	ret = platform_driver_register (&tsi_eth_driver);
	if (ret < 0){
		printk("tsi108_ether_init: error initializing ethernet "
		       "device\n");
		return ret;
	}
	return 0;
}