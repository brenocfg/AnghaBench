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
typedef  int /*<<< orphan*/  kpc_pm_handler_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kpc_reserve_pm_counters (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
kpc_register_pm_handler(kpc_pm_handler_t handler)
{
	return kpc_reserve_pm_counters(0x38, handler, TRUE);
}