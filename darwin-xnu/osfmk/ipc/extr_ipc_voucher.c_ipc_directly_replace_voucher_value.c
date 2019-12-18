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
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  iv_index_t ;
typedef  int /*<<< orphan*/  ipc_voucher_t ;
typedef  scalar_t__ ipc_voucher_attr_manager_t ;
typedef  int /*<<< orphan*/  ipc_voucher_attr_control_t ;

/* Variables and functions */
 scalar_t__ IVAM_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_VALUE_FLAGS_NONE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  iv_key_to_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivace_reference_by_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivace_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivgt_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static kern_return_t
ipc_directly_replace_voucher_value(
	ipc_voucher_t				voucher,
	mach_voucher_attr_key_t 		key,
	mach_voucher_attr_value_handle_t	new_value)
{
	ipc_voucher_attr_manager_t ivam;
	ipc_voucher_attr_control_t ivac;
	iv_index_t save_val_index;
	iv_index_t val_index;
	iv_index_t key_index;
	
	/*
	 * Get the manager for this key_index.
	 * Returns a reference on the control.
	 */
	key_index = iv_key_to_index(key);
	ivgt_lookup(key_index, TRUE, &ivam, &ivac);
	if (IVAM_NULL == ivam)
		return KERN_INVALID_ARGUMENT;

	/* save the current value stored in the forming voucher */
	save_val_index = iv_lookup(voucher, key_index);

	/*
	 * Find or create a slot in the table associated
	 * with this attribute value.  The ivac reference
	 * is transferred to a new value, or consumed if
	 * we find a matching existing value.
	 */
	val_index = ivace_reference_by_value(ivac, new_value,
				MACH_VOUCHER_ATTR_VALUE_FLAGS_NONE);
	iv_set(voucher, key_index, val_index);

	/*
	 * release saved old value from the newly forming voucher
	 * This is saved until the end to avoid churning the
	 * release logic in cases where the same value is returned
	 * as was there before.
	 */
	ivace_release(key_index, save_val_index);
	
	return KERN_SUCCESS;
}