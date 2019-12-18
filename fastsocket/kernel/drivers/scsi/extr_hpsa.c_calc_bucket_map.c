#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int MINIMUM_TRANSFER_BLOCKS ; 

__attribute__((used)) static void  calc_bucket_map(int bucket[], int num_buckets,
	int nsgs, int *bucket_map)
{
	int i, j, b, size;

	/* even a command with 0 SGs requires 4 blocks */
#define MINIMUM_TRANSFER_BLOCKS 4
#define NUM_BUCKETS 8
	/* Note, bucket_map must have nsgs+1 entries. */
	for (i = 0; i <= nsgs; i++) {
		/* Compute size of a command with i SG entries */
		size = i + MINIMUM_TRANSFER_BLOCKS;
		b = num_buckets; /* Assume the biggest bucket */
		/* Find the bucket that is just big enough */
		for (j = 0; j < 8; j++) {
			if (bucket[j] >= size) {
				b = j;
				break;
			}
		}
		/* for a command with i SG entries, use bucket b. */
		bucket_map[i] = b;
	}
}