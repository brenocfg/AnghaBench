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
typedef  int /*<<< orphan*/  dtrace_strkey_f ;
typedef  int /*<<< orphan*/  dtrace_hashbucket_t ;
struct TYPE_3__ {uintptr_t dth_stroffs; uintptr_t dth_nextoffs; uintptr_t dth_prevoffs; int dth_size; int dth_mask; void* dth_tab; int /*<<< orphan*/  dth_getstr; } ;
typedef  TYPE_1__ dtrace_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_hash_t *
dtrace_hash_create(dtrace_strkey_f func, uintptr_t arg, uintptr_t nextoffs, uintptr_t prevoffs)
{
	dtrace_hash_t *hash = kmem_zalloc(sizeof (dtrace_hash_t), KM_SLEEP);

	hash->dth_getstr = func;
	hash->dth_stroffs = arg;
	hash->dth_nextoffs = nextoffs;
	hash->dth_prevoffs = prevoffs;

	hash->dth_size = 1;
	hash->dth_mask = hash->dth_size - 1;

	hash->dth_tab = kmem_zalloc(hash->dth_size *
	    sizeof (dtrace_hashbucket_t *), KM_SLEEP);

	return (hash);
}