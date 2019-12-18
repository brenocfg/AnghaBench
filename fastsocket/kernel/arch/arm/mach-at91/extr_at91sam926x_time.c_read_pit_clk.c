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
typedef  int u32 ;
struct clocksource {int dummy; } ;
typedef  int cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PIT_PIIR ; 
 scalar_t__ PIT_CPIV (int) ; 
 int PIT_PICNT (int) ; 
 int at91_sys_read (int /*<<< orphan*/ ) ; 
 int pit_cnt ; 
 int pit_cycle ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 

__attribute__((used)) static cycle_t read_pit_clk(struct clocksource *cs)
{
	unsigned long flags;
	u32 elapsed;
	u32 t;

	raw_local_irq_save(flags);
	elapsed = pit_cnt;
	t = at91_sys_read(AT91_PIT_PIIR);
	raw_local_irq_restore(flags);

	elapsed += PIT_PICNT(t) * pit_cycle;
	elapsed += PIT_CPIV(t);
	return elapsed;
}