#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  scalar_t__ mach_voucher_attr_value_handle_array_size_t ;
typedef  TYPE_1__* mach_voucher_attr_recipe_t ;
typedef  scalar_t__ mach_voucher_attr_raw_recipe_t ;
typedef  int mach_voucher_attr_raw_recipe_size_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ iv_index_t ;
typedef  scalar_t__ ipc_voucher_t ;
typedef  TYPE_2__* ipc_voucher_attr_manager_t ;
struct TYPE_7__ {scalar_t__ (* ivam_extract_content ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_6__ {int content_size; int /*<<< orphan*/  content; int /*<<< orphan*/  command; int /*<<< orphan*/  previous_voucher; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* IVAM_NULL ; 
 scalar_t__ IV_NULL ; 
 scalar_t__ IV_UNUSED_VALINDEX ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_NO_SPACE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_NOOP ; 
 int MACH_VOUCHER_ATTR_VALUE_MAX_NESTED ; 
 int /*<<< orphan*/  MACH_VOUCHER_NAME_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ iv_key_to_index (int /*<<< orphan*/ ) ; 
 scalar_t__ iv_lookup (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ivace_lookup_values (scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ivgt_lookup (scalar_t__,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

kern_return_t
mach_voucher_extract_attr_recipe(
	ipc_voucher_t				voucher,
	mach_voucher_attr_key_t			key,
	mach_voucher_attr_raw_recipe_t		raw_recipe,
	mach_voucher_attr_raw_recipe_size_t	*in_out_size)
{
	mach_voucher_attr_value_handle_t vals[MACH_VOUCHER_ATTR_VALUE_MAX_NESTED];
	mach_voucher_attr_value_handle_array_size_t vals_count;
	ipc_voucher_attr_manager_t manager;
	mach_voucher_attr_recipe_t recipe;
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

	if (*in_out_size < sizeof(*recipe))
		return KERN_NO_SPACE;

	recipe = (mach_voucher_attr_recipe_t)(void *)raw_recipe;
	recipe->key = key;
	recipe->command = MACH_VOUCHER_ATTR_NOOP;
	recipe->previous_voucher = MACH_VOUCHER_NAME_NULL;
	recipe->content_size = *in_out_size - sizeof(*recipe);

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
					     &recipe->command,
					     recipe->content, &recipe->content_size);
	if (KERN_SUCCESS == kr) {
	  assert(*in_out_size - sizeof(*recipe) >= recipe->content_size);
	  *in_out_size = sizeof(*recipe) + recipe->content_size;
	}

	return kr;
}