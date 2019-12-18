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
struct sh_tmu_priv {int dummy; } ;
struct clocksource {int dummy; } ;
typedef  int cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TCNT ; 
 struct sh_tmu_priv* cs_to_sh_tmu (struct clocksource*) ; 
 int sh_tmu_read (struct sh_tmu_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cycle_t sh_tmu_clocksource_read(struct clocksource *cs)
{
	struct sh_tmu_priv *p = cs_to_sh_tmu(cs);

	return sh_tmu_read(p, TCNT) ^ 0xffffffff;
}