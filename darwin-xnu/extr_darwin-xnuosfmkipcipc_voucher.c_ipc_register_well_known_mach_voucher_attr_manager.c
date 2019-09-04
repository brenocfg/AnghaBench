#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_key_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  size_t iv_index_t ;
typedef  scalar_t__ ipc_voucher_attr_manager_t ;
typedef  TYPE_2__* ipc_voucher_attr_control_t ;
struct TYPE_10__ {scalar_t__ ivgte_manager; int /*<<< orphan*/  ivgte_key; TYPE_2__* ivgte_control; } ;
struct TYPE_9__ {TYPE_1__* ivac_table; } ;
struct TYPE_8__ {scalar_t__ ivace_next; scalar_t__ ivace_index; int /*<<< orphan*/  ivace_persist; void* ivace_made; void* ivace_refs; int /*<<< orphan*/  ivace_value; } ;

/* Variables and functions */
 void* IVACE_REFS_MAX ; 
 TYPE_2__* IVAC_NULL ; 
 scalar_t__ IVAM_NULL ; 
 scalar_t__ IV_HASH_END ; 
 size_t IV_UNUSED_KEYINDEX ; 
 size_t IV_UNUSED_VALINDEX ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* iv_global_table ; 
 size_t iv_hash_value (size_t,int /*<<< orphan*/ ) ; 
 size_t iv_key_to_index (int /*<<< orphan*/ ) ; 
 TYPE_2__* ivac_alloc (size_t) ; 
 int /*<<< orphan*/  ivac_release (TYPE_2__*) ; 
 int /*<<< orphan*/  ivgt_lock () ; 
 int /*<<< orphan*/  ivgt_unlock () ; 

kern_return_t
ipc_register_well_known_mach_voucher_attr_manager(
	ipc_voucher_attr_manager_t manager,
	mach_voucher_attr_value_handle_t default_value,
        mach_voucher_attr_key_t key,
	ipc_voucher_attr_control_t *control)
{
	ipc_voucher_attr_control_t new_control;
	iv_index_t key_index;
	iv_index_t hash_index;

	if (IVAM_NULL == manager)
		return KERN_INVALID_ARGUMENT;

	key_index = iv_key_to_index(key);
	if (IV_UNUSED_KEYINDEX == key_index)
		return KERN_INVALID_ARGUMENT;

	new_control = ivac_alloc(key_index);
	if (IVAC_NULL == new_control)
		return KERN_RESOURCE_SHORTAGE;

	/* insert the default value into slot 0 */
	new_control->ivac_table[IV_UNUSED_VALINDEX].ivace_value = default_value;
	new_control->ivac_table[IV_UNUSED_VALINDEX].ivace_refs = IVACE_REFS_MAX;
	new_control->ivac_table[IV_UNUSED_VALINDEX].ivace_made = IVACE_REFS_MAX;
	new_control->ivac_table[IV_UNUSED_VALINDEX].ivace_persist = TRUE;
	assert(IV_HASH_END == new_control->ivac_table[IV_UNUSED_VALINDEX].ivace_next);

	ivgt_lock();
	if (IVAM_NULL != iv_global_table[key_index].ivgte_manager) {
		ivgt_unlock();
		ivac_release(new_control);
		return KERN_INVALID_ARGUMENT;
	}

	/* fill in the global table slot for this key */
	iv_global_table[key_index].ivgte_manager = manager;
	iv_global_table[key_index].ivgte_control = new_control;
	iv_global_table[key_index].ivgte_key = key;

	/* insert the default value into the hash (in case it is returned later) */
	hash_index = iv_hash_value(key_index, default_value);
	assert(IV_HASH_END == new_control->ivac_table[hash_index].ivace_index);
	new_control->ivac_table[hash_index].ivace_index = IV_UNUSED_VALINDEX;

	ivgt_unlock();
	
	/* return the reference on the new cache control to the caller */
	*control = new_control;

	return KERN_SUCCESS;
}