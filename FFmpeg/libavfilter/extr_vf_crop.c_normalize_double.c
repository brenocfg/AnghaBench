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
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 double INT_MAX ; 
 double INT_MIN ; 
 scalar_t__ isnan (double) ; 
 int lrint (double) ; 

__attribute__((used)) static inline int normalize_double(int *n, double d)
{
    int ret = 0;

    if (isnan(d)) {
        ret = AVERROR(EINVAL);
    } else if (d > INT_MAX || d < INT_MIN) {
        *n = d > INT_MAX ? INT_MAX : INT_MIN;
        ret = AVERROR(EINVAL);
    } else
        *n = lrint(d);

    return ret;
}