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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  il4965_math_div_round (scalar_t__,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static s32
il4965_interpolate_value(s32 x, s32 x1, s32 y1, s32 x2, s32 y2)
{
	s32 val;

	if (x2 == x1)
		return y1;
	else {
		il4965_math_div_round((x2 - x) * (y1 - y2), (x2 - x1), &val);
		return val + y2;
	}
}