#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lithium_t ;
struct TYPE_5__ {int /*<<< orphan*/  rfield; TYPE_2__* lfield; scalar_t__ negative; } ;
typedef  TYPE_1__ ad1843_gain_t ;
struct TYPE_6__ {int nbits; } ;

/* Variables and functions */
 int EINVAL ; 
 int ad1843_get_gain (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  ad1843_write_multi (int /*<<< orphan*/ *,int,TYPE_2__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad1843_set_gain(lithium_t *lith,
			   const ad1843_gain_t *gp,
			   int newval)
{
	unsigned short mask = (1 << gp->lfield->nbits) - 1;

	int lg = newval >> 0 & 0xFF;
	int rg = newval >> 8;
	if (lg < 0 || lg > 100 || rg < 0 || rg > 100)
		return -EINVAL;
	lg = (lg * mask + (mask >> 1)) / 100;
	rg = (rg * mask + (mask >> 1)) / 100;
	if (gp->negative) {
		lg = mask - lg;
		rg = mask - rg;
	}
	ad1843_write_multi(lith, 2, gp->lfield, lg, gp->rfield, rg);
	return ad1843_get_gain(lith, gp);
}