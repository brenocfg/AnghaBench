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
struct TYPE_4__ {int ull_refcount; int /*<<< orphan*/  ull_turnstile; int /*<<< orphan*/  ull_owner; scalar_t__ ull_opcode; scalar_t__ ull_max_nwaiters; scalar_t__ ull_nwaiters; int /*<<< orphan*/  ull_bucket_index; void* ull_saved_key; void* ull_key; } ;
typedef  TYPE_1__ ull_t ;
typedef  void* ulk_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_NULL ; 
 int /*<<< orphan*/  TURNSTILE_NULL ; 
 int /*<<< orphan*/  ULL_INDEX (void**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ull_lock_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ull_nzalloc ; 
 int /*<<< orphan*/  ull_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ull_t *
ull_alloc(ulk_t *key)
{
	ull_t *ull = (ull_t *)zalloc(ull_zone);
	assert(ull != NULL);

	ull->ull_refcount = 1;
	ull->ull_key = *key;
	ull->ull_saved_key = *key;
	ull->ull_bucket_index = ULL_INDEX(key);
	ull->ull_nwaiters = 0;
	ull->ull_max_nwaiters = 0;
	ull->ull_opcode = 0;

	ull->ull_owner = THREAD_NULL;
	ull->ull_turnstile = TURNSTILE_NULL;

	ull_lock_init(ull);

	ull_nzalloc++;
	return ull;
}