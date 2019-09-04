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
 int INT_MAX ; 

__attribute__((used)) static inline int distance_limited(int *a, int *b, int dim, int limit)
{
    int i, dist=0;
    for (i=0; i<dim; i++) {
        dist += (a[i] - b[i])*(a[i] - b[i]);
        if (dist > limit)
            return INT_MAX;
    }

    return dist;
}