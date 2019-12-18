#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lithium_t ;
struct TYPE_4__ {scalar_t__ negative; int /*<<< orphan*/  rfield; TYPE_2__* lfield; } ;
typedef  TYPE_1__ ad1843_gain_t ;
struct TYPE_5__ {int nbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad1843_read_multi (int /*<<< orphan*/ *,int,TYPE_2__*,int*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ad1843_get_gain(lithium_t *lith, const ad1843_gain_t *gp)
{
	int lg, rg;
	unsigned short mask = (1 << gp->lfield->nbits) - 1;

	ad1843_read_multi(lith, 2, gp->lfield, &lg, gp->rfield, &rg);
	if (gp->negative) {
		lg = mask - lg;
		rg = mask - rg;
	}
	lg = (lg * 100 + (mask >> 1)) / mask;
	rg = (rg * 100 + (mask >> 1)) / mask;
	return lg << 0 | rg << 8;
}