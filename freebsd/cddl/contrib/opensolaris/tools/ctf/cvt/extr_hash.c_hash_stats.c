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
 int list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
hash_stats(hash_t *hash, int verbose)
{
	int min = list_count(hash->h_buckets[0]);
	int minidx = 0;
	int max = min;
	int maxidx = 0;
	int tot = min;
	int count;
	int i;

	if (min && verbose)
		printf("%3d: %d\n", 0, min);
	for (i = 1; i < hash->h_nbuckets; i++) {
		count = list_count(hash->h_buckets[i]);
		if (min > count) {
			min = count;
			minidx = i;
		}
		if (max < count) {
			max = count;
			maxidx = i;
		}
		if (count && verbose)
			printf("%3d: %d\n", i, count);
		tot += count;
	}

	printf("Hash statistics:\n");
	printf(" Buckets: %d\n", hash->h_nbuckets);
	printf(" Items  : %d\n", tot);
	printf(" Min/Max: %d in #%d, %d in #%d\n", min, minidx, max, maxidx);
	printf(" Average: %5.2f\n", (float)tot / (float)hash->h_nbuckets);
}