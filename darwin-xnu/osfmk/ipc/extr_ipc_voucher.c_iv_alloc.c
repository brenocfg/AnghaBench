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
typedef  scalar_t__ iv_index_t ;
typedef  int /*<<< orphan*/ * iv_entry_t ;
typedef  TYPE_1__* ipc_voucher_t ;
struct TYPE_5__ {scalar_t__ iv_table_size; int /*<<< orphan*/ * iv_table; int /*<<< orphan*/ * iv_inline_table; int /*<<< orphan*/  iv_port; scalar_t__ iv_hash; scalar_t__ iv_sum; int /*<<< orphan*/  iv_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_NULL ; 
 int /*<<< orphan*/ * IVE_NULL ; 
 scalar_t__ IV_ENTRIES_INLINE ; 
 TYPE_1__* IV_NULL ; 
 int /*<<< orphan*/  IV_UNUSED_VALINDEX ; 
 int /*<<< orphan*/  ipc_voucher_zone ; 
 int /*<<< orphan*/  iv_refgrp ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  os_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

ipc_voucher_t
iv_alloc(iv_index_t entries)
{
	ipc_voucher_t iv;
	iv_index_t i;


	iv = (ipc_voucher_t)zalloc(ipc_voucher_zone);
	if (IV_NULL == iv)
		return IV_NULL;
		
	os_ref_init(&iv->iv_refs, &iv_refgrp);
	iv->iv_sum = 0;
	iv->iv_hash = 0;
	iv->iv_port = IP_NULL;

	if (entries > IV_ENTRIES_INLINE) {
		iv_entry_t table;

		/* TODO - switch to ipc_table method of allocation */
		table = (iv_entry_t) kalloc(sizeof(*table) * entries);
		if (IVE_NULL == table) {
			zfree(ipc_voucher_zone, iv);
			return IV_NULL;
		}
		iv->iv_table = table;
		iv->iv_table_size = entries;
	} else {
		iv->iv_table = iv->iv_inline_table;
		iv->iv_table_size = IV_ENTRIES_INLINE;
	}

	/* initialize the table entries */
	for (i=0; i < iv->iv_table_size; i++)
		iv->iv_table[i] = IV_UNUSED_VALINDEX;
		
	return (iv);
}