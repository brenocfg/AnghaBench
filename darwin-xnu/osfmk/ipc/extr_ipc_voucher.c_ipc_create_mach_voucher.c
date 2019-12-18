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
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_voucher_t ;
typedef  TYPE_1__* ipc_voucher_attr_recipe_t ;
typedef  int ipc_voucher_attr_recipe_size_t ;
typedef  int /*<<< orphan*/ * ipc_voucher_attr_raw_recipe_array_t ;
typedef  int ipc_voucher_attr_raw_recipe_array_size_t ;
struct TYPE_2__ {int content_size; int /*<<< orphan*/  content; int /*<<< orphan*/  previous_voucher; int /*<<< orphan*/  command; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IV_NULL ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ ipc_execute_voucher_recipe_command (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ iv_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_dealloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ iv_dedup (scalar_t__) ; 
 int /*<<< orphan*/  ivgt_keys_in_use ; 

kern_return_t
ipc_create_mach_voucher(
	ipc_voucher_attr_raw_recipe_array_t 		recipes,
	ipc_voucher_attr_raw_recipe_array_size_t	recipe_size,
	ipc_voucher_t 					*new_voucher)
{
	ipc_voucher_attr_recipe_t sub_recipe;
	ipc_voucher_attr_recipe_size_t recipe_used = 0;
	ipc_voucher_t voucher;
	kern_return_t kr = KERN_SUCCESS;

	/* if nothing to do ... */
	if (0 == recipe_size) {
		*new_voucher = IV_NULL;
		return KERN_SUCCESS;
	}

	/* allocate a voucher */
	voucher = iv_alloc(ivgt_keys_in_use);
	if (IV_NULL == voucher)
		return KERN_RESOURCE_SHORTAGE;

	/* iterate over the recipe items */
	while (0 < recipe_size - recipe_used) {

		if (recipe_size - recipe_used < sizeof(*sub_recipe)) {
			kr = KERN_INVALID_ARGUMENT;
			break;
		}

		/* find the next recipe */
		sub_recipe = (ipc_voucher_attr_recipe_t)(void *)&recipes[recipe_used];
		if (recipe_size - recipe_used - sizeof(*sub_recipe) < sub_recipe->content_size) {
			kr = KERN_INVALID_ARGUMENT;
			break;
		}
		recipe_used += sizeof(*sub_recipe) + sub_recipe->content_size;

		kr = ipc_execute_voucher_recipe_command(voucher,
							sub_recipe->key,
							sub_recipe->command,
							sub_recipe->previous_voucher,
							sub_recipe->content,
							sub_recipe->content_size,
							FALSE);
		if (KERN_SUCCESS != kr)
			break;
	}

	if (KERN_SUCCESS == kr) {
		*new_voucher = iv_dedup(voucher);
	} else {
		iv_dealloc(voucher, FALSE);
		*new_voucher = IV_NULL;
	}
	return kr;
}