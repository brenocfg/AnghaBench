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
struct irq_chip {scalar_t__ disable; scalar_t__ shutdown; scalar_t__ end; scalar_t__ typename; scalar_t__ name; scalar_t__ startup; scalar_t__ enable; } ;
struct TYPE_2__ {scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ default_disable ; 
 scalar_t__ default_enable ; 
 scalar_t__ default_shutdown ; 
 scalar_t__ default_startup ; 
 TYPE_1__ dummy_irq_chip ; 

void irq_chip_set_defaults(struct irq_chip *chip)
{
	if (!chip->enable)
		chip->enable = default_enable;
	if (!chip->disable)
		chip->disable = default_disable;
	if (!chip->startup)
		chip->startup = default_startup;
	/*
	 * We use chip->disable, when the user provided its own. When
	 * we have default_disable set for chip->disable, then we need
	 * to use default_shutdown, otherwise the irq line is not
	 * disabled on free_irq():
	 */
	if (!chip->shutdown)
		chip->shutdown = chip->disable != default_disable ?
			chip->disable : default_shutdown;
	if (!chip->name)
		chip->name = chip->typename;
	if (!chip->end)
		chip->end = dummy_irq_chip.end;
}