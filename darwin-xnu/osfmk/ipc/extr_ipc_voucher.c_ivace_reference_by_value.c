#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  int mach_voucher_attr_value_flags_t ;
typedef  TYPE_1__* ivac_entry_t ;
typedef  size_t iv_index_t ;
typedef  TYPE_2__* ipc_voucher_attr_control_t ;
struct TYPE_11__ {size_t ivac_table_size; size_t ivac_freelist; TYPE_1__* ivac_table; int /*<<< orphan*/  ivac_init_table_size; } ;
struct TYPE_10__ {size_t ivace_index; size_t ivace_next; int ivace_refs; int ivace_made; void* ivace_persist; void* ivace_free; int /*<<< orphan*/  ivace_value; } ;

/* Variables and functions */
 void* FALSE ; 
 TYPE_1__* IVACE_NULL ; 
 TYPE_2__* IVAC_NULL ; 
 size_t IV_FREELIST_END ; 
 size_t IV_HASH_END ; 
 size_t IV_HASH_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t IV_UNUSED_VALINDEX ; 
 int MACH_VOUCHER_ATTR_VALUE_FLAGS_PERSIST ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ivac_grow_table (TYPE_2__*) ; 
 int /*<<< orphan*/  ivac_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ivac_release (TYPE_2__*) ; 
 int /*<<< orphan*/  ivac_unlock (TYPE_2__*) ; 

__attribute__((used)) static iv_index_t
ivace_reference_by_value(
	ipc_voucher_attr_control_t	ivac,
	mach_voucher_attr_value_handle_t  	value,
	mach_voucher_attr_value_flags_t          flag)
{
	ivac_entry_t ivace = IVACE_NULL;
	iv_index_t hash_index;
	iv_index_t index;

	if (IVAC_NULL == ivac) {
		return IV_UNUSED_VALINDEX;
	}

 	ivac_lock(ivac);
restart:
	hash_index = IV_HASH_VAL(ivac->ivac_init_table_size, value);
	index = ivac->ivac_table[hash_index].ivace_index;
	while (index != IV_HASH_END) {
		assert(index < ivac->ivac_table_size);
		ivace = &ivac->ivac_table[index];
		assert(!ivace->ivace_free);

		if (ivace->ivace_value == value)
			break;

		assert(ivace->ivace_next != index);
		index = ivace->ivace_next;
	}

	/* found it? */
	if (index != IV_HASH_END) { 
		/* only add reference on non-persistent value */
		if (!ivace->ivace_persist) {
			ivace->ivace_refs++;
			ivace->ivace_made++;
		}

		ivac_unlock(ivac);
		ivac_release(ivac);
		return index;
	}

	/* insert new entry in the table */
	index = ivac->ivac_freelist;
	if (IV_FREELIST_END == index) {
		/* freelist empty */
		ivac_grow_table(ivac);
		goto restart;
	}

	/* take the entry off the freelist */
	ivace = &ivac->ivac_table[index];
	ivac->ivac_freelist = ivace->ivace_next;

	/* initialize the new entry */
	ivace->ivace_value = value;
	ivace->ivace_refs = 1;
	ivace->ivace_made = 1;
	ivace->ivace_free = FALSE;
	ivace->ivace_persist = (flag & MACH_VOUCHER_ATTR_VALUE_FLAGS_PERSIST) ? TRUE : FALSE;

	/* insert the new entry in the proper hash chain */
	ivace->ivace_next = ivac->ivac_table[hash_index].ivace_index;
	ivac->ivac_table[hash_index].ivace_index = index;
	ivac_unlock(ivac);

	/* donated passed in ivac reference to new entry */

	return index;
}