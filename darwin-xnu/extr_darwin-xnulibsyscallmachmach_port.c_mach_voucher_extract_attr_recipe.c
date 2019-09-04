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
typedef  int /*<<< orphan*/  mach_voucher_attr_raw_recipe_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ MACH_SEND_INVALID_DEST ; 
 scalar_t__ _kernelrpc_mach_voucher_extract_attr_recipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mach_voucher_extract_attr_recipe_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
mach_voucher_extract_attr_recipe(
	mach_port_name_t voucher,
	mach_voucher_attr_key_t key,
	mach_voucher_attr_raw_recipe_t recipe,
	mach_msg_type_number_t *recipe_size)
{
	kern_return_t rv;

	rv = mach_voucher_extract_attr_recipe_trap(voucher, key, recipe, recipe_size);

	if (rv == MACH_SEND_INVALID_DEST)
		rv = _kernelrpc_mach_voucher_extract_attr_recipe(voucher, key, recipe, recipe_size);

	return rv;
}