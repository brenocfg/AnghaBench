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
struct parport {int dummy; } ;
struct TYPE_2__ {int rd_data_reg_sel; } ;

/* Variables and functions */
 unsigned char PARPORT_CONTROL_STROBE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ sound_ym ; 

__attribute__((used)) static unsigned char
parport_atari_read_control(struct parport *p)
{
	unsigned long flags;
	unsigned char control = 0;

	local_irq_save(flags);
	sound_ym.rd_data_reg_sel = 14;
	if (!(sound_ym.rd_data_reg_sel & (1 << 5)))
		control = PARPORT_CONTROL_STROBE;
	local_irq_restore(flags);
	return control;
}