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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ force_all_ctrs ; 
 int /*<<< orphan*/  kpc_pm_handler ; 
 int /*<<< orphan*/  kpc_pm_has_custom_config ; 

boolean_t
kpc_controls_fixed_counters(void)
{
	return !kpc_pm_handler || force_all_ctrs || !kpc_pm_has_custom_config;
}