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
struct e100_serial {size_t line; } ;
struct TYPE_2__ {unsigned char cd_mask; unsigned char* cd_shadow; unsigned char* cd_port; } ;

/* Variables and functions */
 TYPE_1__* e100_modem_pins ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static inline void
e100_cd_out(struct e100_serial *info, int set)
{
#ifndef CONFIG_SVINTO_SIM
	/* CD is active low */
	{
		unsigned char mask = e100_modem_pins[info->line].cd_mask;
		unsigned long flags;

		local_irq_save(flags);
		*e100_modem_pins[info->line].cd_shadow &= ~mask;
		*e100_modem_pins[info->line].cd_shadow |= (set ? 0 : mask);
		*e100_modem_pins[info->line].cd_port = *e100_modem_pins[info->line].cd_shadow;
		local_irq_restore(flags);
	}
#endif
}