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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int rv40_loop_filter_strength (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int,int*,int*) ; 

__attribute__((used)) static int rv40_v_loop_filter_strength(uint8_t *src, ptrdiff_t stride,
                                       int beta, int beta2, int edge,
                                       int *p1, int *q1)
{
    return rv40_loop_filter_strength(src, 1, stride, beta, beta2, edge, p1, q1);
}