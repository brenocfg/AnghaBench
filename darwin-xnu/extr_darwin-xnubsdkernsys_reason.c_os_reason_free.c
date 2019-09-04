#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* os_reason_t ;
struct TYPE_6__ {scalar_t__ osr_refcount; int /*<<< orphan*/  osr_lock; } ;

/* Variables and functions */
 TYPE_1__* OS_REASON_NULL ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_reason_dealloc_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  os_reason_lock_grp ; 
 int /*<<< orphan*/  os_reason_zone ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
os_reason_free(os_reason_t cur_reason)
{
	if (cur_reason == OS_REASON_NULL) {
		return;
	}

	lck_mtx_lock(&cur_reason->osr_lock);

	if (cur_reason->osr_refcount == 0) {
		panic("os_reason_free called on reason with zero refcount");
	}

	cur_reason->osr_refcount--;
	if (cur_reason->osr_refcount != 0) {
		lck_mtx_unlock(&cur_reason->osr_lock);
		return;
	}

	os_reason_dealloc_buffer(cur_reason);

	lck_mtx_unlock(&cur_reason->osr_lock);
	lck_mtx_destroy(&cur_reason->osr_lock, os_reason_lock_grp);

	zfree(os_reason_zone, cur_reason);
}