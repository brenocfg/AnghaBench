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
typedef  scalar_t__ u64 ;
struct runtime_sc {scalar_t__ x; scalar_t__ y; scalar_t__ dx; scalar_t__ dy; int /*<<< orphan*/  sm2; int /*<<< orphan*/  sm1; } ;

/* Variables and functions */
 scalar_t__ seg_x2y (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64
rtsc_x2y(struct runtime_sc *rtsc, u64 x)
{
	u64 y;

	if (x <= rtsc->x)
		y = rtsc->y;
	else if (x <= rtsc->x + rtsc->dx)
		/* y belongs to the 1st segment */
		y = rtsc->y + seg_x2y(x - rtsc->x, rtsc->sm1);
	else
		/* y belongs to the 2nd segment */
		y = rtsc->y + rtsc->dy
		    + seg_x2y(x - rtsc->x - rtsc->dx, rtsc->sm2);
	return y;
}