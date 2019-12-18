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
 int /*<<< orphan*/  rv40_weak_loop_filter (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const,int const,int const,int const,int const,int const,int const,int const) ; 

__attribute__((used)) static void rv40_v_weak_loop_filter(uint8_t *src, const ptrdiff_t stride,
                                    const int filter_p1, const int filter_q1,
                                    const int alpha, const int beta,
                                    const int lim_p0q0, const int lim_q1,
                                    const int lim_p1)
{
    rv40_weak_loop_filter(src, 1, stride, filter_p1, filter_q1,
                          alpha, beta, lim_p0q0, lim_q1, lim_p1);
}