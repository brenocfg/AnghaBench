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
struct dm_transaction_manager {int is_clone; struct dm_transaction_manager* real; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dm_transaction_manager* kmalloc (int,int /*<<< orphan*/ ) ; 

struct dm_transaction_manager *dm_tm_create_non_blocking_clone(struct dm_transaction_manager *real)
{
	struct dm_transaction_manager *tm;

	tm = kmalloc(sizeof(*tm), GFP_KERNEL);
	if (tm) {
		tm->is_clone = 1;
		tm->real = real;
	}

	return tm;
}