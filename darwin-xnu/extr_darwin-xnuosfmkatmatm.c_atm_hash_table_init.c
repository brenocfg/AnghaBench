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
struct TYPE_2__ {int /*<<< orphan*/  hash_list_lock; int /*<<< orphan*/  hash_list; } ;

/* Variables and functions */
 int ATM_MAX_HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  atm_lock_attr ; 
 int /*<<< orphan*/  atm_lock_grp ; 
 TYPE_1__* atm_value_hash_table ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
atm_hash_table_init()
{
	int i;

	for (i = 0; i < ATM_MAX_HASH_TABLE_SIZE; i++) {
		queue_init(&atm_value_hash_table[i].hash_list);
		lck_mtx_init(&atm_value_hash_table[i].hash_list_lock, &atm_lock_grp, &atm_lock_attr);
	}
}