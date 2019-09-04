#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  int mach_voucher_attr_recipe_command_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  scalar_t__ mach_voucher_attr_content_t ;
typedef  int mach_voucher_attr_content_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  iv_index_t ;
typedef  TYPE_1__* ipc_voucher_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  iv_table_size; } ;

/* Variables and functions */
 TYPE_1__* IV_NULL ; 
 int /*<<< orphan*/  IV_UNUSED_VALINDEX ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_CAPABILITY ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  MACH_VOUCHER_ATTR_COPY 131 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_ALL ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_NONE ; 
#define  MACH_VOUCHER_ATTR_REDEEM 130 
#define  MACH_VOUCHER_ATTR_REMOVE 129 
#define  MACH_VOUCHER_ATTR_SET_VALUE_HANDLE 128 
 int /*<<< orphan*/  ipc_directly_replace_voucher_value (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_replace_voucher_value (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  iv_index_to_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_key_to_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_lookup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivace_reference_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivace_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivgt_keys_in_use ; 

__attribute__((used)) static kern_return_t
ipc_execute_voucher_recipe_command(
	ipc_voucher_t 				voucher,
	mach_voucher_attr_key_t			key,
	mach_voucher_attr_recipe_command_t	command,
	ipc_voucher_t				prev_iv,
	mach_voucher_attr_content_t		content,
	mach_voucher_attr_content_size_t	content_size,
	boolean_t				key_priv)
{
	iv_index_t prev_val_index;
	iv_index_t val_index;
	kern_return_t kr;

	switch (command) {

	/*
	 * MACH_VOUCHER_ATTR_COPY
	 *	Copy the attribute(s) from the previous voucher to the new
	 *	one.  A wildcard key is an acceptable value - indicating a
	 *	desire to copy all the attribute values from the previous
	 *	voucher.
	 */
	case MACH_VOUCHER_ATTR_COPY:
		
		/* no recipe data on a copy */
		if (0 < content_size)
			return KERN_INVALID_ARGUMENT;

		/* nothing to copy from? - done */
		if (IV_NULL == prev_iv)
			return KERN_SUCCESS;

		if (MACH_VOUCHER_ATTR_KEY_ALL == key) {
			iv_index_t limit, j;

			/* reconcile possible difference in voucher sizes */
			limit = (prev_iv->iv_table_size < voucher->iv_table_size) ?
			        prev_iv->iv_table_size :
				voucher->iv_table_size;

			/* wildcard matching */
			for (j = 0; j < limit; j++) {
				/* release old value being replaced */
				val_index = iv_lookup(voucher, j);
				ivace_release(j, val_index);

				/* replace with reference to prev voucher's value */
				prev_val_index = iv_lookup(prev_iv, j);
				ivace_reference_by_index(j, prev_val_index);
				iv_set(voucher, j, prev_val_index);
			}
		} else {
			iv_index_t key_index;

			/* copy just one key */
			key_index = iv_key_to_index(key);
			if (ivgt_keys_in_use < key_index)
				return KERN_INVALID_ARGUMENT;

			/* release old value being replaced */
			val_index = iv_lookup(voucher, key_index);
			ivace_release(key_index, val_index);

			/* replace with reference to prev voucher's value */
			prev_val_index = iv_lookup(prev_iv, key_index);
			ivace_reference_by_index(key_index, prev_val_index);
			iv_set(voucher, key_index, prev_val_index);
		}
		break;

	/*
	 * MACH_VOUCHER_ATTR_REMOVE
	 *	Remove the attribute(s) from the under construction voucher.
	 *	A wildcard key is an acceptable value - indicating a desire
	 *	to remove all the attribute values set up so far in the voucher.
	 *	If a previous voucher is specified, only remove the value it
	 *	it matches the value in the previous voucher.
	 */
	case MACH_VOUCHER_ATTR_REMOVE:
		/* no recipe data on a remove */
		if (0 < content_size)
			return KERN_INVALID_ARGUMENT;

		if (MACH_VOUCHER_ATTR_KEY_ALL == key) {
			iv_index_t limit, j;

			/* reconcile possible difference in voucher sizes */
			limit = (IV_NULL == prev_iv) ? voucher->iv_table_size :
				((prev_iv->iv_table_size < voucher->iv_table_size) ?
				 prev_iv->iv_table_size : voucher->iv_table_size);

			/* wildcard matching */
			for (j = 0; j < limit; j++) {
				val_index = iv_lookup(voucher, j);

				/* If not matched in previous, skip */
				if (IV_NULL != prev_iv) {
					prev_val_index = iv_lookup(prev_iv, j);
					if (val_index != prev_val_index)
						continue;
				}
				/* release and clear */
				ivace_release(j, val_index);
				iv_set(voucher, j, IV_UNUSED_VALINDEX);
			}
		} else {
			iv_index_t key_index;

			/* copy just one key */
			key_index = iv_key_to_index(key);
			if (ivgt_keys_in_use < key_index)
				return KERN_INVALID_ARGUMENT;

			val_index = iv_lookup(voucher, key_index);

			/* If not matched in previous, skip */
			if (IV_NULL != prev_iv) {
				prev_val_index = iv_lookup(prev_iv, key_index);
				if (val_index != prev_val_index)
					break;
			}

			/* release and clear */
			ivace_release(key_index, val_index);
			iv_set(voucher, key_index, IV_UNUSED_VALINDEX);
		}
		break;

	/*
	 * MACH_VOUCHER_ATTR_SET_VALUE_HANDLE
	 *	Use key-privilege to set a value handle for the attribute directly,
	 *	rather than triggering a callback into the attribute manager to
	 *	interpret a recipe to generate the value handle.
	 */
	case MACH_VOUCHER_ATTR_SET_VALUE_HANDLE:
		if (key_priv) {
			mach_voucher_attr_value_handle_t new_value;

			if (sizeof(mach_voucher_attr_value_handle_t) != content_size)
				return KERN_INVALID_ARGUMENT;
			
			new_value = *(mach_voucher_attr_value_handle_t *)(void *)content;
			kr = ipc_directly_replace_voucher_value(voucher,
								key,
								new_value);
			if (KERN_SUCCESS != kr)
				return kr;
		} else
			return KERN_INVALID_CAPABILITY;
		break;

	/*
	 * MACH_VOUCHER_ATTR_REDEEM
	 *	Redeem the attribute(s) from the previous voucher for a possibly
	 *	new value in the new voucher. A wildcard key is an acceptable value,
	 *	indicating a desire to redeem all the values.
	 */ 	
	case MACH_VOUCHER_ATTR_REDEEM:

		if (MACH_VOUCHER_ATTR_KEY_ALL == key) {
			iv_index_t limit, j;

			/* reconcile possible difference in voucher sizes */
			if (IV_NULL != prev_iv)
				limit = (prev_iv->iv_table_size < voucher->iv_table_size) ?
					prev_iv->iv_table_size :
					voucher->iv_table_size;
			else
				limit = voucher->iv_table_size;

			/* wildcard matching */
			for (j = 0; j < limit; j++) {
				mach_voucher_attr_key_t j_key;

				j_key = iv_index_to_key(j);

				/* skip non-existent managers */
				if (MACH_VOUCHER_ATTR_KEY_NONE == j_key)
					continue;

				/* get the new value from redeem (skip empty previous) */
				kr = ipc_replace_voucher_value(voucher,
							       j_key,
							       command,
							       prev_iv,
							       content,
							       content_size);
				if (KERN_SUCCESS != kr)
					return kr;
			}
			break;
		}
		/* fall thru for single key redemption */

	/*
	 * DEFAULT:
	 *	Replace the current value for the <voucher, key> pair with whatever
	 *	value the resource manager returns for the command and recipe
	 *	combination provided.
	 */
	default:
		kr = ipc_replace_voucher_value(voucher,
					       key,
					       command,
					       prev_iv,
					       content,
					       content_size);
		if (KERN_SUCCESS != kr)
			return kr;

		break;
	}
	return KERN_SUCCESS;
}