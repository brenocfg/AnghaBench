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
struct sport_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int tcr1; int rcr1; unsigned int rcr2; unsigned int rclkdiv; unsigned int rfsdiv; } ;

/* Variables and functions */
 int EBUSY ; 
 int RSPEN ; 
 int /*<<< orphan*/  SSYNC () ; 
 int TSPEN ; 

int sport_config_rx(struct sport_device *sport, unsigned int rcr1,
		unsigned int rcr2, unsigned int clkdiv, unsigned int fsdiv)
{
	if ((sport->regs->tcr1 & TSPEN) || (sport->regs->rcr1 & RSPEN))
		return -EBUSY;

	sport->regs->rcr1 = rcr1;
	sport->regs->rcr2 = rcr2;
	sport->regs->rclkdiv = clkdiv;
	sport->regs->rfsdiv = fsdiv;

	SSYNC();

	return 0;
}