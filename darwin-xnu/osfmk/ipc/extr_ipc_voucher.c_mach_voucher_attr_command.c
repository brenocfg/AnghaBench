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
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_content_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_content_size_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_command_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  iv_index_t ;
typedef  scalar_t__ ipc_voucher_t ;
typedef  TYPE_1__* ipc_voucher_attr_manager_t ;
typedef  int /*<<< orphan*/  ipc_voucher_attr_control_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* ivam_command ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* IVAM_NULL ; 
 scalar_t__ IV_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int MACH_VOUCHER_ATTR_VALUE_MAX_NESTED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  iv_key_to_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivac_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivace_lookup_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivgt_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
mach_voucher_attr_command(
	ipc_voucher_t						voucher,
	mach_voucher_attr_key_t				key,
	mach_voucher_attr_command_t			command,
	mach_voucher_attr_content_t			in_content,
	mach_voucher_attr_content_size_t	in_content_size,
	mach_voucher_attr_content_t			out_content,
	mach_voucher_attr_content_size_t	*out_content_size)
{
	mach_voucher_attr_value_handle_t vals[MACH_VOUCHER_ATTR_VALUE_MAX_NESTED];
	mach_voucher_attr_value_handle_array_size_t vals_count;
	ipc_voucher_attr_manager_t manager;
	ipc_voucher_attr_control_t control;
	iv_index_t value_index;
	iv_index_t key_index;
	kern_return_t kr;


	if (IV_NULL == voucher)
		return KERN_INVALID_ARGUMENT;

	key_index = iv_key_to_index(key);

	/*
	 * Get the manager for this key_index.
	 * Allowing commands against the default value
	 * for an attribute means that we have to hold
	 * reference on the attribute manager control
	 * to keep the manager around during the command
	 * execution.
	 */
	ivgt_lookup(key_index, TRUE, &manager, &control);
	if (IVAM_NULL == manager) {
		return KERN_INVALID_ARGUMENT;
	}

	/*
	 * Get the values for this <voucher, key> pair
	 * to pass to the attribute manager.  It is still
	 * permissible to execute a command against the
	 * default value (empty value array).
	 */
	value_index = iv_lookup(voucher, key_index);
	ivace_lookup_values(key_index, value_index,
			    vals, &vals_count);

	/* callout to manager */
	kr = (manager->ivam_command)(manager, key, 
				     vals, vals_count,
				     command,
				     in_content, in_content_size,
				     out_content, out_content_size);

	/* release reference on control */
	ivac_release(control);

	return kr;
}