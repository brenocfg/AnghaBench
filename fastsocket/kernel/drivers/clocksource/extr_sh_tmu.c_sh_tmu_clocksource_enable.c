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
struct sh_tmu_priv {int /*<<< orphan*/  rate; } ;
struct clocksource {int shift; int /*<<< orphan*/  mult; } ;

/* Variables and functions */
 int /*<<< orphan*/  clocksource_hz2mult (int /*<<< orphan*/ ,int) ; 
 struct sh_tmu_priv* cs_to_sh_tmu (struct clocksource*) ; 
 int sh_tmu_enable (struct sh_tmu_priv*) ; 

__attribute__((used)) static int sh_tmu_clocksource_enable(struct clocksource *cs)
{
	struct sh_tmu_priv *p = cs_to_sh_tmu(cs);
	int ret;

	ret = sh_tmu_enable(p);
	if (ret)
		return ret;

	/* TODO: calculate good shift from rate and counter bit width */
	cs->shift = 10;
	cs->mult = clocksource_hz2mult(p->rate, cs->shift);
	return 0;
}