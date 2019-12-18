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
typedef  scalar_t__ mach_voucher_attr_value_handle_array_size_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_recipe_command_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_content_t ;
typedef  scalar_t__ mach_voucher_attr_content_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ iv_index_t ;
typedef  scalar_t__ ipc_voucher_t ;
typedef  TYPE_1__* ipc_voucher_attr_manager_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* ivam_extract_content ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* IVAM_NULL ; 
 scalar_t__ IV_NULL ; 
 scalar_t__ IV_UNUSED_VALINDEX ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MACH_VOUCHER_ATTR_VALUE_MAX_NESTED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ iv_key_to_index (int /*<<< orphan*/ ) ; 
 scalar_t__ iv_lookup (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ivace_lookup_values (scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ivgt_lookup (scalar_t__,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

kern_return_t
mach_voucher_extract_attr_content(
	ipc_voucher_t				voucher,
	mach_voucher_attr_key_t			key,
	mach_voucher_attr_content_t		content,
	mach_voucher_attr_content_size_t	*in_out_size)
{
	mach_voucher_attr_value_handle_t vals[MACH_VOUCHER_ATTR_VALUE_MAX_NESTED];
	mach_voucher_attr_value_handle_array_size_t vals_count;
	mach_voucher_attr_recipe_command_t command;
	ipc_voucher_attr_manager_t manager;
	iv_index_t value_index;
	iv_index_t key_index;
	kern_return_t kr;


	if (IV_NULL == voucher)
		return KERN_INVALID_ARGUMENT;

	key_index = iv_key_to_index(key);

	value_index = iv_lookup(voucher, key_index);
	if (IV_UNUSED_VALINDEX == value_index) {
		*in_out_size = 0;
		return KERN_SUCCESS;
	}

	/*
	 * Get the manager for this key_index.  The
	 * existence of a non-default value for this
	 * slot within our voucher will keep the
	 * manager referenced during the callout.
	 */
	ivgt_lookup(key_index, FALSE, &manager, NULL);
	if (IVAM_NULL == manager) {
		return KERN_INVALID_ARGUMENT;
	}

	/*
	 * Get the value(s) to pass to the manager
	 * for this value_index.
	 */
	ivace_lookup_values(key_index, value_index,
			    vals, &vals_count);
	assert(0 < vals_count);

	/* callout to manager */
	
	kr = (manager->ivam_extract_content)(manager, key, 
					     vals, vals_count,
					     &command,
					     content, in_out_size);
	return kr;
}