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
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_to_sh_tmu (struct clocksource*) ; 
 int /*<<< orphan*/  sh_tmu_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_tmu_clocksource_disable(struct clocksource *cs)
{
	sh_tmu_disable(cs_to_sh_tmu(cs));
}