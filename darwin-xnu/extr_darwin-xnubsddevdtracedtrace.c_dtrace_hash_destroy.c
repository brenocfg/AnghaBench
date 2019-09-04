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
typedef  int /*<<< orphan*/  dtrace_hashbucket_t ;
struct TYPE_4__ {int dth_size; struct TYPE_4__* dth_tab; } ;
typedef  TYPE_1__ dtrace_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 

__attribute__((used)) static void
dtrace_hash_destroy(dtrace_hash_t *hash)
{
#if DEBUG
	int i;

	for (i = 0; i < hash->dth_size; i++)
		ASSERT(hash->dth_tab[i] == NULL);
#endif

	kmem_free(hash->dth_tab,
	    hash->dth_size * sizeof (dtrace_hashbucket_t *));
	kmem_free(hash, sizeof (dtrace_hash_t));
}