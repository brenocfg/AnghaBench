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
struct mpc_table {int dummy; } ;

/* Variables and functions */
 scalar_t__ es7000_apic_is_cluster () ; 
 int es7000_mps_ret ; 

__attribute__((used)) static int es7000_mps_oem_check_cluster(struct mpc_table *mpc, char *oem,
		char *productid)
{
	int ret = es7000_mps_ret;

	return ret && es7000_apic_is_cluster();
}