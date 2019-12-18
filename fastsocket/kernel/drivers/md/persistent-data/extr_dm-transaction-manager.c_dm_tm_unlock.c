#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dm_transaction_manager {int dummy; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int dm_bm_unlock (struct dm_block*) ; 

int dm_tm_unlock(struct dm_transaction_manager *tm, struct dm_block *b)
{
	return dm_bm_unlock(b);
}