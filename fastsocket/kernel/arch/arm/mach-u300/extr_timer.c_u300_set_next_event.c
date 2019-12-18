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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ U300_TIMER_APP_DGPT1 ; 
 unsigned long U300_TIMER_APP_DGPT1_TIMER_DISABLE ; 
 scalar_t__ U300_TIMER_APP_EGPT1 ; 
 unsigned long U300_TIMER_APP_EGPT1_TIMER_ENABLE ; 
 scalar_t__ U300_TIMER_APP_GPT1IE ; 
 unsigned long U300_TIMER_APP_GPT1IE_IRQ_DISABLE ; 
 unsigned long U300_TIMER_APP_GPT1IE_IRQ_ENABLE ; 
 scalar_t__ U300_TIMER_APP_GPT1TC ; 
 scalar_t__ U300_TIMER_APP_RGPT1 ; 
 unsigned long U300_TIMER_APP_RGPT1_TIMER_RESET ; 
 scalar_t__ U300_TIMER_APP_SGPT1M ; 
 unsigned long U300_TIMER_APP_SGPT1M_MODE_ONE_SHOT ; 
 scalar_t__ U300_TIMER_APP_VBASE ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int u300_set_next_event(unsigned long cycles,
			       struct clock_event_device *evt)

{
	/* Disable interrupts on GPT1 */
	writel(U300_TIMER_APP_GPT1IE_IRQ_DISABLE,
	       U300_TIMER_APP_VBASE + U300_TIMER_APP_GPT1IE);
	/* Disable GP1 while we're reprogramming it. */
	writel(U300_TIMER_APP_DGPT1_TIMER_DISABLE,
	       U300_TIMER_APP_VBASE + U300_TIMER_APP_DGPT1);
	/* Reset the General Purpose timer 1. */
	writel(U300_TIMER_APP_RGPT1_TIMER_RESET,
	       U300_TIMER_APP_VBASE + U300_TIMER_APP_RGPT1);
	/* IRQ in n * cycles */
	writel(cycles, U300_TIMER_APP_VBASE + U300_TIMER_APP_GPT1TC);
	/*
	 * We run one shot per tick here! (This is necessary to reconfigure,
	 * the timer will tilt if you don't!)
	 */
	writel(U300_TIMER_APP_SGPT1M_MODE_ONE_SHOT,
	       U300_TIMER_APP_VBASE + U300_TIMER_APP_SGPT1M);
	/* Enable timer interrupts */
	writel(U300_TIMER_APP_GPT1IE_IRQ_ENABLE,
	       U300_TIMER_APP_VBASE + U300_TIMER_APP_GPT1IE);
	/* Then enable the OS timer again */
	writel(U300_TIMER_APP_EGPT1_TIMER_ENABLE,
	       U300_TIMER_APP_VBASE + U300_TIMER_APP_EGPT1);
	return 0;
}