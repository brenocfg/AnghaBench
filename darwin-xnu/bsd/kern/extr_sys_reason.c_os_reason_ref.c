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
typedef  TYPE_1__* os_reason_t ;
struct TYPE_4__ {scalar_t__ osr_refcount; int /*<<< orphan*/  osr_lock; } ;

/* Variables and functions */
 TYPE_1__* OS_REASON_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ os_add_overflow (scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
os_reason_ref(os_reason_t cur_reason)
{
	if (cur_reason == OS_REASON_NULL) {
		return;
	}

	lck_mtx_lock(&cur_reason->osr_lock);

	assert(cur_reason->osr_refcount > 0);
	if (os_add_overflow(cur_reason->osr_refcount, 1, &cur_reason->osr_refcount)) {
		panic("os reason refcount overflow");
	}

	lck_mtx_unlock(&cur_reason->osr_lock);

	return;
}