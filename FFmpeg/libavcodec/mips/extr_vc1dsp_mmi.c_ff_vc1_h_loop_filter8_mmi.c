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

/* Variables and functions */
 int /*<<< orphan*/  vc1_loop_filter (int /*<<< orphan*/ *,int,int,int,int) ; 

void ff_vc1_h_loop_filter8_mmi(uint8_t *src, int stride, int pq)
{
    vc1_loop_filter(src, stride, 1, 8, pq);
}