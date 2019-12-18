#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_array_size_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_value_flags_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_recipe_command_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_content_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_content_size_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  iv_index_t ;
typedef  scalar_t__ ipc_voucher_t ;
typedef  TYPE_1__* ipc_voucher_attr_manager_t ;
typedef  int /*<<< orphan*/  ipc_voucher_attr_control_t ;
struct TYPE_5__ {scalar_t__ (* ivam_get_value ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ;} ;

/* Variables and functions */
 TYPE_1__* IVAM_NULL ; 
 scalar_t__ IV_NULL ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 int MACH_VOUCHER_ATTR_VALUE_MAX_NESTED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  iv_key_to_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_release (scalar_t__) ; 
 int /*<<< orphan*/  iv_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivac_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivace_lookup_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivace_reference_by_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivace_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivgt_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static kern_return_t
ipc_replace_voucher_value(
	ipc_voucher_t				voucher,
	mach_voucher_attr_key_t 		key,
	mach_voucher_attr_recipe_command_t	command,
	ipc_voucher_t				prev_voucher,
	mach_voucher_attr_content_t		content,
	mach_voucher_attr_content_size_t        content_size)
{
	mach_voucher_attr_value_handle_t previous_vals[MACH_VOUCHER_ATTR_VALUE_MAX_NESTED];
	mach_voucher_attr_value_handle_array_size_t previous_vals_count;
	mach_voucher_attr_value_handle_t new_value;
	mach_voucher_attr_value_flags_t new_flag;
	ipc_voucher_t new_value_voucher;
	ipc_voucher_attr_manager_t ivam;
	ipc_voucher_attr_control_t ivac;
	iv_index_t prev_val_index;
	iv_index_t save_val_index;
	iv_index_t val_index;
	iv_index_t key_index;
	kern_return_t kr;
	
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
	 * Get the previous value(s) for this key creation.
	 * If a previous voucher is specified, they come from there.
	 * Otherwise, they come from the intermediate values already
	 * in the forming voucher.
	 */
	prev_val_index = (IV_NULL != prev_voucher) ?
		         iv_lookup(prev_voucher, key_index) :
		         save_val_index;
	ivace_lookup_values(key_index, prev_val_index,
			    previous_vals, &previous_vals_count);

	/* Call out to resource manager to get new value */
	new_value_voucher = IV_NULL;
	kr = (ivam->ivam_get_value)(
				    ivam, key, command,
				    previous_vals, previous_vals_count,
				    content, content_size,
				    &new_value, &new_flag, &new_value_voucher);
	if (KERN_SUCCESS != kr) {
		ivac_release(ivac);
		return kr;
	}

	/* TODO: value insertion from returned voucher */
	if (IV_NULL != new_value_voucher)
		iv_release(new_value_voucher);

	/*
	 * Find or create a slot in the table associated
	 * with this attribute value.  The ivac reference
	 * is transferred to a new value, or consumed if
	 * we find a matching existing value.
	 */
	val_index = ivace_reference_by_value(ivac, new_value, new_flag);
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