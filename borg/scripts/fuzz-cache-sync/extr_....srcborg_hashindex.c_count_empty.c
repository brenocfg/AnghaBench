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
struct TYPE_4__ {int num_buckets; } ;
typedef  TYPE_1__ HashIndex ;

/* Variables and functions */
 scalar_t__ BUCKET_IS_EMPTY (TYPE_1__*,int) ; 

int
count_empty(HashIndex *index)
{   /* count empty (never used) buckets. this does NOT include deleted buckets (tombstones).
     * TODO: if we ever change HashHeader, save the count there so we do not need this function.
     */
    int i, count = 0, capacity = index->num_buckets;
    for(i = 0; i < capacity; i++) {
        if(BUCKET_IS_EMPTY(index, i))
            count++;
    }
    return count;
}