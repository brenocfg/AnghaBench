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
struct TYPE_3__ {int /*<<< orphan*/ * p; int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ st_percent_t ;
typedef  int /*<<< orphan*/  patch_t ;
typedef  int /*<<< orphan*/  boolean ;

/* Variables and functions */
 int /*<<< orphan*/  STlib_initNum (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int) ; 

void
STlib_initPercent
( st_percent_t*		p,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  boolean*		on,
  patch_t*		percent )
{
    STlib_initNum(&p->n, x, y, pl, num, on, 3);
    p->p = percent;
}