#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  scalar_t__ mach_voucher_attr_value_handle_array_size_t ;
typedef  TYPE_1__* mach_voucher_attr_recipe_t ;
typedef  int mach_voucher_attr_recipe_size_t ;
typedef  int /*<<< orphan*/ * mach_voucher_attr_raw_recipe_array_t ;
typedef  int mach_voucher_attr_raw_recipe_array_size_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  scalar_t__ mach_voucher_attr_content_size_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ iv_index_t ;
typedef  TYPE_2__* ipc_voucher_t ;
typedef  TYPE_3__* ipc_voucher_attr_manager_t ;
struct TYPE_12__ {scalar_t__ (* ivam_extract_content ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_11__ {scalar_t__ iv_table_size; } ;
struct TYPE_10__ {scalar_t__ content_size; int /*<<< orphan*/  content; int /*<<< orphan*/  command; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* IVAM_NULL ; 
 TYPE_2__* IV_NULL ; 
 scalar_t__ IV_UNUSED_VALINDEX ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_NO_SPACE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_NOOP ; 
 int MACH_VOUCHER_ATTR_VALUE_MAX_NESTED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  iv_index_to_key (scalar_t__) ; 
 scalar_t__ iv_lookup (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ivace_lookup_values (scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ivgt_lookup (scalar_t__,int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

kern_return_t
mach_voucher_extract_all_attr_recipes(
	ipc_voucher_t					voucher,
	mach_voucher_attr_raw_recipe_array_t		recipes,
	mach_voucher_attr_raw_recipe_array_size_t	*in_out_size)
{
	mach_voucher_attr_recipe_size_t recipe_size = *in_out_size;
	mach_voucher_attr_recipe_size_t recipe_used = 0;
	iv_index_t key_index;

	if (IV_NULL == voucher)
		return KERN_INVALID_ARGUMENT;

	for (key_index = 0; key_index < voucher->iv_table_size; key_index++) {
		mach_voucher_attr_value_handle_t vals[MACH_VOUCHER_ATTR_VALUE_MAX_NESTED];
		mach_voucher_attr_value_handle_array_size_t vals_count;
		mach_voucher_attr_content_size_t content_size;
		ipc_voucher_attr_manager_t manager;
		mach_voucher_attr_recipe_t recipe;
		mach_voucher_attr_key_t key;
		iv_index_t value_index;
		kern_return_t kr;

		/* don't output anything for a default value */
		value_index = iv_lookup(voucher, key_index);
		if (IV_UNUSED_VALINDEX == value_index)
			continue;

		if (recipe_size - recipe_used < sizeof(*recipe))
			return KERN_NO_SPACE;

		/*
		 * Get the manager for this key_index.  The
		 * existence of a non-default value for this
		 * slot within our voucher will keep the
		 * manager referenced during the callout.
		 */
		ivgt_lookup(key_index, FALSE, &manager, NULL);
		assert(IVAM_NULL != manager);
		if (IVAM_NULL == manager) {
			continue;
		}

		recipe = (mach_voucher_attr_recipe_t)(void *)&recipes[recipe_used];
		content_size = recipe_size - recipe_used - sizeof(*recipe);

		/*
		 * Get the value(s) to pass to the manager
		 * for this value_index.
		 */
		ivace_lookup_values(key_index, value_index,
				    vals, &vals_count);
		assert(0 < vals_count);

		key = iv_index_to_key(key_index);

		recipe->key = key;
		recipe->command = MACH_VOUCHER_ATTR_NOOP;
		recipe->content_size = content_size;

		/* callout to manager */
		kr = (manager->ivam_extract_content)(manager, key, 
					     vals, vals_count,
					     &recipe->command,
					     recipe->content, &recipe->content_size);
		if (KERN_SUCCESS != kr)
			return kr;

		assert(recipe->content_size <= content_size);
		recipe_used += sizeof(*recipe) + recipe->content_size;
	}

	*in_out_size = recipe_used;
	return KERN_SUCCESS;
}