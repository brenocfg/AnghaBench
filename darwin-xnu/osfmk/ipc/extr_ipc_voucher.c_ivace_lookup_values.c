#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * mach_voucher_attr_value_handle_array_t ;
typedef  int mach_voucher_attr_value_handle_array_size_t ;
typedef  TYPE_1__* ivac_entry_t ;
typedef  size_t iv_index_t ;
typedef  TYPE_2__* ipc_voucher_attr_control_t ;
struct TYPE_9__ {TYPE_2__* ivgte_control; } ;
struct TYPE_8__ {size_t ivac_table_size; TYPE_1__* ivac_table; } ;
struct TYPE_7__ {scalar_t__ ivace_refs; int /*<<< orphan*/  ivace_value; } ;

/* Variables and functions */
 TYPE_2__* IVAC_NULL ; 
 size_t IV_UNUSED_VALINDEX ; 
 size_t MACH_VOUCHER_ATTR_KEY_NUM_WELL_KNOWN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* iv_global_table ; 
 int /*<<< orphan*/  ivac_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ivac_unlock (TYPE_2__*) ; 

__attribute__((used)) static void
ivace_lookup_values(
	iv_index_t		 		key_index,
	iv_index_t				value_index,
	mach_voucher_attr_value_handle_array_t		values,
	mach_voucher_attr_value_handle_array_size_t	*count)
{
	ipc_voucher_attr_control_t ivac;
	ivac_entry_t ivace;

	if (IV_UNUSED_VALINDEX == value_index ||
	    MACH_VOUCHER_ATTR_KEY_NUM_WELL_KNOWN <= key_index) {
		*count = 0;
		return;
	}

	ivac = iv_global_table[key_index].ivgte_control;
	assert(IVAC_NULL != ivac);

	/*
	 * Get the entry and then the linked values.
	 */
	ivac_lock(ivac);
	assert(value_index < ivac->ivac_table_size);
	ivace = &ivac->ivac_table[value_index];

	/*
	 * TODO: support chained values (for effective vouchers).
	 */
	assert(ivace->ivace_refs > 0);
	values[0] = ivace->ivace_value;
	ivac_unlock(ivac);
	*count = 1;
}