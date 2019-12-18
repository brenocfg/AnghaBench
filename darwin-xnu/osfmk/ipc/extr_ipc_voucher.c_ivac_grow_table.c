#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ivac_entry_t ;
typedef  int /*<<< orphan*/  ivac_entry ;
typedef  int iv_index_t ;
typedef  TYPE_2__* ipc_voucher_attr_control_t ;
struct TYPE_14__ {int ivac_is_growing; int ivac_table_size; int ivac_freelist; TYPE_1__* ivac_table; } ;
struct TYPE_13__ {int ivace_next; } ;

/* Variables and functions */
 int IVAC_ENTRIES_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ivac_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ivac_sleep (TYPE_2__*) ; 
 int /*<<< orphan*/  ivac_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ivac_wakeup (TYPE_2__*) ; 
 int /*<<< orphan*/  ivace_copy_data (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ivace_reset_data (TYPE_1__*,int) ; 
 TYPE_1__* kalloc (int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static void
ivac_grow_table(ipc_voucher_attr_control_t ivac)
{
	iv_index_t i = 0;

	/* NOTE: do not modify *_table and *_size values once set */
	ivac_entry_t new_table = NULL, old_table = NULL;
	iv_index_t new_size, old_size;

	if (ivac->ivac_is_growing) {
		ivac_sleep(ivac);
		return;
	}

	ivac->ivac_is_growing = 1;
	if (ivac->ivac_table_size >= IVAC_ENTRIES_MAX) {
		panic("Cannot grow ipc space beyond IVAC_ENTRIES_MAX. Some process is leaking vouchers");
		return;
	}

	old_size = ivac->ivac_table_size;
	ivac_unlock(ivac);

	new_size = old_size * 2;

	assert(new_size > old_size);
	assert(new_size < IVAC_ENTRIES_MAX);

	new_table = kalloc(sizeof(ivac_entry) * new_size);
	if (!new_table){
		panic("Failed to grow ivac table to size %d\n", new_size);
		return;
	}

	/* setup the free list for new entries */
	for (i = old_size; i < new_size; i++) {
		ivace_reset_data(&new_table[i], i+1);
	}

	ivac_lock(ivac);
	
	for (i = 0; i < ivac->ivac_table_size; i++){
		ivace_copy_data(&ivac->ivac_table[i], &new_table[i]);
	}

	old_table = ivac->ivac_table;

	ivac->ivac_table = new_table;
	ivac->ivac_table_size = new_size;
	
	/* adding new free entries at head of freelist */
	ivac->ivac_table[new_size - 1].ivace_next = ivac->ivac_freelist;
	ivac->ivac_freelist = old_size;
	ivac->ivac_is_growing = 0;
	ivac_wakeup(ivac);

	if (old_table){
		ivac_unlock(ivac);
		kfree(old_table, old_size * sizeof(ivac_entry));
		ivac_lock(ivac);
	}
}