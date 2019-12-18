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
struct sh_cmt_priv {int /*<<< orphan*/  rate; scalar_t__ total_cycles; } ;
struct clocksource {int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_CLOCKSOURCE ; 
 int /*<<< orphan*/  clocksource_hz2mult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sh_cmt_priv* cs_to_sh_cmt (struct clocksource*) ; 
 int sh_cmt_start (struct sh_cmt_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_cmt_clocksource_enable(struct clocksource *cs)
{
	struct sh_cmt_priv *p = cs_to_sh_cmt(cs);
	int ret;

	p->total_cycles = 0;

	ret = sh_cmt_start(p, FLAG_CLOCKSOURCE);
	if (ret)
		return ret;

	/* TODO: calculate good shift from rate and counter bit width */
	cs->shift = 0;
	cs->mult = clocksource_hz2mult(p->rate, cs->shift);
	return 0;
}