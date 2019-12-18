#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ JETSAM_PRIORITY_IDLE ; 
 scalar_t__ MEMSTAT_BUCKET_COUNT ; 
 TYPE_1__* memstat_bucket ; 

int
memorystatus_get_proccnt_upto_priority(int32_t max_bucket_index)
{
	int32_t	i = JETSAM_PRIORITY_IDLE;
	int count = 0;

	if (max_bucket_index >= MEMSTAT_BUCKET_COUNT) {
                return(-1);
        }

	while(i <= max_bucket_index) {
		count += memstat_bucket[i++].count;
	}

	return count;
}