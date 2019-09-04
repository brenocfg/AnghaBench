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
 int FFABS (int const) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT16_MAX ; 

__attribute__((used)) static int16_t max_abs_value_w16(const int16_t* vector, int length)
{
    int i = 0, absolute = 0, maximum = 0;

    if (vector == NULL || length <= 0) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        absolute = FFABS(vector[i]);
        if (absolute > maximum)
            maximum = absolute;
    }

    // Guard the case for abs(-32768).
    return FFMIN(maximum, INT16_MAX);
}