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
struct lx6464es {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lx_irq_set (struct lx6464es*,int) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

void lx_irq_enable(struct lx6464es *chip)
{
	snd_printdd("->lx_irq_enable\n");
	lx_irq_set(chip, 1);
}