#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ sample_counter_reg; scalar_t__ irq_status_reg; scalar_t__ start_reg; scalar_t__ scan_pre_timer_high_reg; scalar_t__ scan_pre_timer_low_reg; scalar_t__ scan_timer_high_reg; scalar_t__ scan_timer_low_reg; scalar_t__ chan_pre_timer_reg; scalar_t__ chan_timer_reg; scalar_t__ data_reg; scalar_t__ channel_list_reg; scalar_t__ status_reg; scalar_t__ ctrl_reg; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {scalar_t__ me4000_regbase; TYPE_1__ ai_context; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_PDEBUG (char*) ; 
 scalar_t__ ME4000_AI_CHANNEL_LIST_REG ; 
 scalar_t__ ME4000_AI_CHAN_PRE_TIMER_REG ; 
 scalar_t__ ME4000_AI_CHAN_TIMER_REG ; 
 scalar_t__ ME4000_AI_CTRL_REG ; 
 scalar_t__ ME4000_AI_DATA_REG ; 
 scalar_t__ ME4000_AI_SAMPLE_COUNTER_REG ; 
 scalar_t__ ME4000_AI_SCAN_PRE_TIMER_HIGH_REG ; 
 scalar_t__ ME4000_AI_SCAN_PRE_TIMER_LOW_REG ; 
 scalar_t__ ME4000_AI_SCAN_TIMER_HIGH_REG ; 
 scalar_t__ ME4000_AI_SCAN_TIMER_LOW_REG ; 
 scalar_t__ ME4000_AI_START_REG ; 
 scalar_t__ ME4000_AI_STATUS_REG ; 
 scalar_t__ ME4000_IRQ_STATUS_REG ; 
 TYPE_2__* info ; 

__attribute__((used)) static int init_ai_context(struct comedi_device *dev)
{

	CALL_PDEBUG("In init_ai_context()\n");

	info->ai_context.irq = info->irq;

	info->ai_context.ctrl_reg = info->me4000_regbase + ME4000_AI_CTRL_REG;
	info->ai_context.status_reg =
	    info->me4000_regbase + ME4000_AI_STATUS_REG;
	info->ai_context.channel_list_reg =
	    info->me4000_regbase + ME4000_AI_CHANNEL_LIST_REG;
	info->ai_context.data_reg = info->me4000_regbase + ME4000_AI_DATA_REG;
	info->ai_context.chan_timer_reg =
	    info->me4000_regbase + ME4000_AI_CHAN_TIMER_REG;
	info->ai_context.chan_pre_timer_reg =
	    info->me4000_regbase + ME4000_AI_CHAN_PRE_TIMER_REG;
	info->ai_context.scan_timer_low_reg =
	    info->me4000_regbase + ME4000_AI_SCAN_TIMER_LOW_REG;
	info->ai_context.scan_timer_high_reg =
	    info->me4000_regbase + ME4000_AI_SCAN_TIMER_HIGH_REG;
	info->ai_context.scan_pre_timer_low_reg =
	    info->me4000_regbase + ME4000_AI_SCAN_PRE_TIMER_LOW_REG;
	info->ai_context.scan_pre_timer_high_reg =
	    info->me4000_regbase + ME4000_AI_SCAN_PRE_TIMER_HIGH_REG;
	info->ai_context.start_reg = info->me4000_regbase + ME4000_AI_START_REG;
	info->ai_context.irq_status_reg =
	    info->me4000_regbase + ME4000_IRQ_STATUS_REG;
	info->ai_context.sample_counter_reg =
	    info->me4000_regbase + ME4000_AI_SAMPLE_COUNTER_REG;

	return 0;
}