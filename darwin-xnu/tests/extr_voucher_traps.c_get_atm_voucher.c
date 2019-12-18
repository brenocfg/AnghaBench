#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  r ;
struct TYPE_2__ {int /*<<< orphan*/  command; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ mach_voucher_attr_recipe_data_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_raw_recipe_array_t ;
typedef  scalar_t__ mach_port_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_ATM_CREATE ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_ATM ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  host_create_mach_voucher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  mach_host_self () ; 

__attribute__((used)) static mach_port_t get_atm_voucher(void)
{
	mach_voucher_attr_recipe_data_t r = {
		.key = MACH_VOUCHER_ATTR_KEY_ATM,
		.command = MACH_VOUCHER_ATTR_ATM_CREATE
	};
	mach_port_t port = MACH_PORT_NULL;
	kern_return_t kr = host_create_mach_voucher(mach_host_self(),
	                                            (mach_voucher_attr_raw_recipe_array_t)&r,
	                                            sizeof(r), &port);
	T_ASSERT_MACH_SUCCESS(kr, "Create ATM voucher: 0x%x", (unsigned int)port);

	return port;
}