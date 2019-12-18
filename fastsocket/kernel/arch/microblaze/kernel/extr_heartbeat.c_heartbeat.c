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

/* Variables and functions */
 int FSHIFT ; 
 int* avenrun ; 
 scalar_t__ base_addr ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 

void heartbeat(void)
{
	static unsigned int cnt, period, dist;

	if (base_addr) {
		if (cnt == 0 || cnt == dist)
			out_be32(base_addr, 1);
		else if (cnt == 7 || cnt == dist + 7)
			out_be32(base_addr, 0);

		if (++cnt > period) {
			cnt = 0;
			/*
			 * The hyperbolic function below modifies the heartbeat
			 * period length in dependency of the current (5min)
			 * load. It goes through the points f(0)=126, f(1)=86,
			 * f(5)=51, f(inf)->30.
			 */
			period = ((672 << FSHIFT) / (5 * avenrun[0] +
						(7 << FSHIFT))) + 30;
			dist = period / 4;
		}
	}
}