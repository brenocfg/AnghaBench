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
struct TYPE_3__ {int h_nbuckets; int /*<<< orphan*/ * h_buckets; } ;
typedef  TYPE_1__ hash_t ;

/* Variables and functions */
 scalar_t__ list_count (int /*<<< orphan*/ ) ; 

int
hash_count(hash_t *hash)
{
	int num, i;

	for (num = 0, i = 0; i < hash->h_nbuckets; i++)
		num += list_count(hash->h_buckets[i]);

	return (num);
}