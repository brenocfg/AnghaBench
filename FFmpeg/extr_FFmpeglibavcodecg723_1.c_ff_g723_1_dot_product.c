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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int av_sat_add32 (int,int) ; 
 int ff_dot_product (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

int ff_g723_1_dot_product(const int16_t *a, const int16_t *b, int length)
{
    int sum = ff_dot_product(a, b, length);
    return av_sat_add32(sum, sum);
}