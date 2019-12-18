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
struct TYPE_3__ {int h_nbuckets; int /*<<< orphan*/ ** h_buckets; } ;
typedef  TYPE_1__ hash_t ;

/* Variables and functions */
 int list_iter (int /*<<< orphan*/ *,int (*) (void*,void*),void*) ; 

int
hash_iter(hash_t *hash, int (*fun)(void *, void *), void *private)
{
	int cumrc = 0;
	int cbrc;
	int i;

	for (i = 0; i < hash->h_nbuckets; i++) {
		if (hash->h_buckets[i] != NULL) {
			if ((cbrc = list_iter(hash->h_buckets[i], fun,
			    private)) < 0)
				return (cbrc);
			cumrc += cbrc;
		}
	}

	return (cumrc);
}