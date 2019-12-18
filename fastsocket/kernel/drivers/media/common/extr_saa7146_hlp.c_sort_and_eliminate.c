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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int sort_and_eliminate(u32* values, int* count)
{
	int low = 0, high = 0, top = 0, temp = 0;
	int cur = 0, next = 0;

	/* sanity checks */
	if( (0 > *count) || (NULL == values) ) {
		return -EINVAL;
	}

	/* bubble sort the first @count items of the array @values */
	for( top = *count; top > 0; top--) {
		for( low = 0, high = 1; high < top; low++, high++) {
			if( values[low] > values[high] ) {
				temp = values[low];
				values[low] = values[high];
				values[high] = temp;
			}
		}
	}

	/* remove duplicate items */
	for( cur = 0, next = 1; next < *count; next++) {
		if( values[cur] != values[next])
			values[++cur] = values[next];
	}

	*count = cur + 1;

	return 0;
}