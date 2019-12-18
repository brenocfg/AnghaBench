#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ulk_pid; scalar_t__ ulk_addr; } ;
struct TYPE_8__ {int ull_refcount; int /*<<< orphan*/  ull_bucket_index; int /*<<< orphan*/  ull_hash_link; TYPE_1__ ull_key; } ;
typedef  TYPE_2__ ull_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  remqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ull_assert_owned (TYPE_2__*) ; 
 int /*<<< orphan*/  ull_bucket_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ull_bucket_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ull_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ull_unlock (TYPE_2__*) ; 

__attribute__((used)) static void
ull_put(ull_t *ull)
{
	ull_assert_owned(ull);
	int refcount = --ull->ull_refcount;
	assert(refcount == 0 ? (ull->ull_key.ulk_pid == 0 && ull->ull_key.ulk_addr == 0) : 1);
	ull_unlock(ull);

	if (refcount > 0) {
		return;
	}

	ull_bucket_lock(ull->ull_bucket_index);
	remqueue(&ull->ull_hash_link);
	ull_bucket_unlock(ull->ull_bucket_index);

	ull_free(ull);
}