#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t iv_index_t ;
typedef  TYPE_1__* ipc_voucher_t ;
struct TYPE_3__ {size_t iv_table_size; size_t* iv_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
iv_set(ipc_voucher_t iv, 
       iv_index_t key_index,
       iv_index_t value_index)
{
	assert(key_index < iv->iv_table_size);
	iv->iv_table[key_index] = value_index;
}