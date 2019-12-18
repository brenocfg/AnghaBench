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
struct TYPE_3__ {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_1__ ccv_rect_t ;

/* Variables and functions */

__attribute__((used)) inline static int ccv_rect_is_zero(ccv_rect_t rect)
{
	return rect.x == 0 && rect.y == 0 && rect.width == 0 && rect.height == 0;
}