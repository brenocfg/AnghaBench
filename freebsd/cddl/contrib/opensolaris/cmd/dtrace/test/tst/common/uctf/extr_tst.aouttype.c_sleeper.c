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
struct TYPE_3__ {int /*<<< orphan*/  fr_salad; } ;
typedef  TYPE_1__ season_7_lisa_the_vegetarian_t ;

/* Variables and functions */
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 

int
sleeper(season_7_lisa_the_vegetarian_t *lp)
{
	for (;;) {
		sleep(lp->fr_salad);
	}
	/*NOTREACHED*/
	return (0);
}