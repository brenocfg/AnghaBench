#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ raw_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_write_can_lock (TYPE_1__*) ; 
 scalar_t__ _raw_compare_and_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int spin_retry ; 

int _raw_write_trylock_retry(raw_rwlock_t *rw)
{
	int count = spin_retry;

	while (count-- > 0) {
		if (!__raw_write_can_lock(rw))
			continue;
		if (_raw_compare_and_swap(&rw->lock, 0, 0x80000000) == 0)
			return 1;
	}
	return 0;
}