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
typedef  int int16_t ;

/* Variables and functions */
 int FFMIN (int const,int) ; 

__attribute__((used)) static int array_min_int16(const int16_t *array, int nel)
{
    int i, min = array[0];
    for (i = 1; i < nel; i++)
        min = FFMIN(array[i], min);
    return min;
}