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
struct timeval {int tv_sec; } ;
struct TYPE_3__ {scalar_t__ lcv; struct timeval lcv_tv; } ;
typedef  TYPE_1__ hil_mlc ;

/* Variables and functions */
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 

__attribute__((used)) static int hilse_init_lcv(hil_mlc *mlc, int unused)
{
	struct timeval tv;

	do_gettimeofday(&tv);

	if (mlc->lcv && (tv.tv_sec - mlc->lcv_tv.tv_sec) < 5)
		return -1;

	mlc->lcv_tv = tv;
	mlc->lcv = 0;

	return 0;
}