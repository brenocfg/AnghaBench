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
typedef  int uint64_t ;
struct bintime {int sec; scalar_t__ frac; } ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  bintime_addns (struct bintime*,int) ; 
 int /*<<< orphan*/  bintime_addx (struct bintime*,int) ; 
 int /*<<< orphan*/  bintime_addxns (struct bintime*,int,int) ; 
 int /*<<< orphan*/  bintime_subx (struct bintime*,int) ; 
 int multi_overflow (int,int) ; 
 int ticks_per_sec ; 

__attribute__((used)) static struct bintime
scale_delta(uint64_t delta, uint64_t tick_scale_x, uint64_t s_scale_ns, int64_t s_adj_nsx)
{
	uint64_t sec, new_ns, over;
	struct bintime bt;

	bt.sec = 0;
	bt.frac = 0;

	/*
	 * If more than one second is elapsed,
	 * scale fully elapsed seconds using scale factors for seconds.
	 * s_scale_ns -> scales sec to ns.
	 * s_adj_nsx -> additional adj expressed in 64 bit frac of ns to apply to each sec.
	 */
	if (delta > ticks_per_sec) {
		sec = (delta/ticks_per_sec);
		new_ns = sec * s_scale_ns;
		bintime_addns(&bt, new_ns);
		if (s_adj_nsx) {
			if (sec == 1) {
				/* shortcut, no overflow can occur */
				if (s_adj_nsx > 0)
					bintime_addx(&bt, (uint64_t)s_adj_nsx/ (uint64_t)NSEC_PER_SEC);
				else
					bintime_subx(&bt, (uint64_t)-s_adj_nsx/ (uint64_t)NSEC_PER_SEC);
			}
			else{
				/*
				 * s_adj_nsx is 64 bit frac of ns.
				 * sec*s_adj_nsx might overflow in int64_t.
				 * use bintime_addxns to not lose overflowed ns.
				 */
				bintime_addxns(&bt, sec, s_adj_nsx);
			}
		}
		delta = (delta % ticks_per_sec);
        }

	over = multi_overflow(tick_scale_x, delta);
	if(over){
		bt.sec += over;
	}

	/*
	 * scale elapsed ticks using the scale factor for ticks.
	 */
	bintime_addx(&bt, delta * tick_scale_x);

	return bt;
}