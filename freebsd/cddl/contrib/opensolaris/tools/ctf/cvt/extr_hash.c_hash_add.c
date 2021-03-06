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
struct TYPE_3__ {int (* h_hashfn ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/ * h_buckets; int /*<<< orphan*/  h_nbuckets; } ;
typedef  TYPE_1__ hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,void*) ; 
 int stub1 (int /*<<< orphan*/ ,void*) ; 

void
hash_add(hash_t *hash, void *key)
{
	int bucket = hash->h_hashfn(hash->h_nbuckets, key);

	list_add(&hash->h_buckets[bucket], key);
}