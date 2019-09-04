#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ ccv_margin_t ;

/* Variables and functions */

__attribute__((used)) inline static ccv_margin_t ccv_margin(int left, int top, int right, int bottom)
{
	ccv_margin_t margin;
	margin.left = left;
	margin.top = top;
	margin.right = right;
	margin.bottom = bottom;
	return margin;
}