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

__attribute__((used)) static inline float distance_from_edge(int x, int max)
{
    int dx = (max/2) - x;
    if (dx < 0) dx = -dx;
    dx = (max/2) + 1 - dx;
    dx *= 2;
    float dist = (float)dx/max;
    if (dist > 1) dist = 1;
    return dist;
}