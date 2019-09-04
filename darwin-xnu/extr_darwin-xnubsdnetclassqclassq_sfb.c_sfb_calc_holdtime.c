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
struct sfb {int /*<<< orphan*/  sfb_holdtime; } ;
struct TYPE_2__ {unsigned int holdtime; scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOLDTIME_MAX ; 
 int /*<<< orphan*/  HOLDTIME_MIN ; 
 scalar_t__ SFB_RANDOM (struct sfb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_nsectimer (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ sfb_holdtime ; 
 TYPE_1__* sfb_ttbl ; 

__attribute__((used)) static void
sfb_calc_holdtime(struct sfb *sp, u_int64_t outbw)
{
	u_int64_t holdtime;

	if (sfb_holdtime != 0) {
		holdtime = sfb_holdtime;
	} else if (outbw == 0) {
		holdtime = SFB_RANDOM(sp, HOLDTIME_MIN, HOLDTIME_MAX);
	} else {
		unsigned int n, i;

		n = sfb_ttbl[0].holdtime;
		for (i = 0; sfb_ttbl[i].speed != 0; i++) {
			if (outbw < sfb_ttbl[i].speed)
				break;
			n = sfb_ttbl[i].holdtime;
		}
		holdtime = n;
	}
	net_nsectimer(&holdtime, &sp->sfb_holdtime);
}