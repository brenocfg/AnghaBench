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
typedef  int /*<<< orphan*/  RCCMPEntry ;

/* Variables and functions */
 int NBUCKETS ; 
 int RADIX_PASSES ; 
 int /*<<< orphan*/  radix_count (int /*<<< orphan*/ *,int,int**) ; 
 int /*<<< orphan*/  radix_sort_pass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static void radix_sort(RCCMPEntry *data, RCCMPEntry *tmp, int size)
{
    int buckets[RADIX_PASSES][NBUCKETS];
    radix_count(data, size, buckets);
    radix_sort_pass(tmp, data, size, buckets[0], 0);
    radix_sort_pass(data, tmp, size, buckets[1], 1);
    if (buckets[2][NBUCKETS - 1] || buckets[3][NBUCKETS - 1]) {
        radix_sort_pass(tmp, data, size, buckets[2], 2);
        radix_sort_pass(data, tmp, size, buckets[3], 3);
    }
}