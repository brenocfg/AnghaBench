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

void eedi2_sort_metrics( int *order, const int length )
{
    int i;
    for( i = 1; i < length; ++i )
    {
        int j = i;
        const int temp = order[j];
        while( j > 0 && order[j-1] > temp )
        {
            order[j] = order[j-1];
            --j;
        }
        order[j] = temp;
    }
}