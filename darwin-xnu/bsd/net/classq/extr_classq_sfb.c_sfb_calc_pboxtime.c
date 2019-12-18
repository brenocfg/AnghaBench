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
typedef  scalar_t__ u_int64_t ;
struct sfb {int /*<<< orphan*/  sfb_pboxfreeze; int /*<<< orphan*/  sfb_pboxtime; } ;
struct TYPE_2__ {unsigned int pboxtime; scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBOXTIME_MAX ; 
 int /*<<< orphan*/  PBOXTIME_MIN ; 
 scalar_t__ SFB_RANDOM (struct sfb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_nsectimer (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_timerclear (int /*<<< orphan*/ *) ; 
 scalar_t__ sfb_pboxtime ; 
 TYPE_1__* sfb_ttbl ; 

__attribute__((used)) static void
sfb_calc_pboxtime(struct sfb *sp, u_int64_t outbw)
{
	u_int64_t pboxtime;

	if (sfb_pboxtime != 0) {
		pboxtime = sfb_pboxtime;
	} else if (outbw == 0) {
		pboxtime = SFB_RANDOM(sp, PBOXTIME_MIN, PBOXTIME_MAX);
	} else {
		unsigned int n, i;

		n = sfb_ttbl[0].pboxtime;
		for (i = 0; sfb_ttbl[i].speed != 0; i++) {
			if (outbw < sfb_ttbl[i].speed)
				break;
			n = sfb_ttbl[i].pboxtime;
		}
		pboxtime = n;
	}
	net_nsectimer(&pboxtime, &sp->sfb_pboxtime);
	net_timerclear(&sp->sfb_pboxfreeze);
}