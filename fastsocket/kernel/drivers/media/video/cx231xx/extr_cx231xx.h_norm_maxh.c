#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ max_range_640_480; } ;
struct cx231xx {int norm; TYPE_1__ board; } ;

/* Variables and functions */
 int V4L2_STD_625_50 ; 

__attribute__((used)) static inline unsigned int norm_maxh(struct cx231xx *dev)
{
	if (dev->board.max_range_640_480)
		return 480;
	else
		return (dev->norm & V4L2_STD_625_50) ? 576 : 480;
}