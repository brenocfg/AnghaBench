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
 scalar_t__ Float2Int (float) ; 

float Fmaxf(float x, float y)
{
	if (x > y || !(y == y))
		return x;
	else if (y > x || !(x == x))
		return y;
	else if (x != 0.f)
		return x;
	else
		return Float2Int(x) == 0 ? x : y;
}