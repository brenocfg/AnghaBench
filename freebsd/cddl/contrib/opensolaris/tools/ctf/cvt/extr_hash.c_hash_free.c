#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int h_nbuckets; struct TYPE_5__* h_buckets; } ;
typedef  TYPE_1__ hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_free (TYPE_1__,void (*) (void*,void*),void*) ; 

void
hash_free(hash_t *hash, void (*datafree)(void *, void *), void *private)
{
	int i;

	if (hash == NULL)
		return;

	for (i = 0; i < hash->h_nbuckets; i++)
		list_free(hash->h_buckets[i], datafree, private);
	free(hash->h_buckets);
	free(hash);
}