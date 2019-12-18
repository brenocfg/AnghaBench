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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOT_SUPPORTED ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  atm_diagnostic_config ; 
 int /*<<< orphan*/  commpage_update_atm_diagnostic_config (int /*<<< orphan*/ ) ; 
 scalar_t__ disable_atm ; 

kern_return_t
atm_set_diagnostic_config(uint32_t diagnostic_config)
{
	if (disable_atm)
		return KERN_NOT_SUPPORTED;

	atm_diagnostic_config = diagnostic_config;
	commpage_update_atm_diagnostic_config(atm_diagnostic_config);

	return KERN_SUCCESS;
}