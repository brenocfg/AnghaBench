#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_attr_recipe_command_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ iv_index_t ;
typedef  TYPE_1__* ipc_voucher_t ;
typedef  TYPE_2__* ipc_voucher_attr_recipe_t ;
typedef  int /*<<< orphan*/ * ipc_voucher_attr_raw_recipe_array_t ;
typedef  int ipc_voucher_attr_raw_recipe_array_size_t ;
typedef  TYPE_3__* ipc_voucher_attr_manager_t ;
typedef  int ipc_voucher_attr_manager_flags ;
struct TYPE_11__ {int ivam_flags; } ;
struct TYPE_10__ {scalar_t__ content_size; TYPE_1__* previous_voucher; int /*<<< orphan*/  command; int /*<<< orphan*/  key; } ;
struct TYPE_9__ {scalar_t__ iv_table_size; } ;

/* Variables and functions */
 int FALSE ; 
 TYPE_3__* IVAM_NULL ; 
 TYPE_1__* IV_NULL ; 
 scalar_t__ IV_UNUSED_VALINDEX ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_COPY ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_ALL ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  iv_index_to_key (scalar_t__) ; 
 scalar_t__ iv_lookup (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ivgt_lookup (scalar_t__,int,TYPE_3__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static kern_return_t
ipc_voucher_prepare_processing_recipe(
	ipc_voucher_t voucher,
	ipc_voucher_attr_raw_recipe_array_t recipes,
	ipc_voucher_attr_raw_recipe_array_size_t *in_out_size,
	mach_voucher_attr_recipe_command_t command,
	ipc_voucher_attr_manager_flags flags,
	int *need_processing)
{
	ipc_voucher_attr_raw_recipe_array_size_t recipe_size = *in_out_size;
	ipc_voucher_attr_raw_recipe_array_size_t recipe_used = 0;
	iv_index_t key_index;
	ipc_voucher_attr_recipe_t recipe;
	
	if (IV_NULL == voucher)
		return KERN_INVALID_ARGUMENT;
	
	/* Setup a recipe to copy all attributes. */
	if (recipe_size < sizeof(*recipe))
			return KERN_NO_SPACE;

	*need_processing = FALSE;
	recipe = (ipc_voucher_attr_recipe_t)(void *)&recipes[recipe_used];
	recipe->key = MACH_VOUCHER_ATTR_KEY_ALL;
	recipe->command = MACH_VOUCHER_ATTR_COPY;
	recipe->previous_voucher = voucher;
	recipe->content_size = 0;
	recipe_used += sizeof(*recipe) + recipe->content_size;

	for (key_index = 0; key_index < voucher->iv_table_size; key_index++) {
		ipc_voucher_attr_manager_t manager;
		mach_voucher_attr_key_t key;
		iv_index_t value_index;

		/* don't output anything for a default value */
		value_index = iv_lookup(voucher, key_index);
		if (IV_UNUSED_VALINDEX == value_index)
			continue;

		if (recipe_size - recipe_used < sizeof(*recipe))
			return KERN_NO_SPACE;

		recipe = (ipc_voucher_attr_recipe_t)(void *)&recipes[recipe_used];
		
		/*
		 * Get the manager for this key_index. The
		 * existence of a non-default value for this
		 * slot within our voucher will keep the
		 * manager referenced during the callout.
		 */
		ivgt_lookup(key_index, FALSE, &manager, NULL);
		assert(IVAM_NULL != manager);
		if (IVAM_NULL == manager) {
			continue;
		}

		/* Check if the supported flag is set in the manager */
		if ((manager->ivam_flags & flags) == 0)
			continue;
		
		key = iv_index_to_key(key_index);

		recipe->key = key;
		recipe->command = command;
		recipe->content_size = 0;
		recipe->previous_voucher = voucher;

		recipe_used += sizeof(*recipe) + recipe->content_size;
		*need_processing = TRUE;
	}

	*in_out_size = recipe_used;
	return KERN_SUCCESS;
}