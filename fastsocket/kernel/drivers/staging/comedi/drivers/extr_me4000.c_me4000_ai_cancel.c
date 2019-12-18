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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl_reg; } ;
struct TYPE_4__ {TYPE_1__ ai_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_PDEBUG (char*) ; 
 unsigned long ME4000_AI_CTRL_BIT_IMMEDIATE_STOP ; 
 unsigned long ME4000_AI_CTRL_BIT_STOP ; 
 TYPE_2__* info ; 
 unsigned long me4000_inl (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me4000_outl (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int me4000_ai_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	unsigned long tmp;

	CALL_PDEBUG("In me4000_ai_cancel()\n");

	/* Stop any running conversion */
	tmp = me4000_inl(dev, info->ai_context.ctrl_reg);
	tmp &= ~(ME4000_AI_CTRL_BIT_STOP | ME4000_AI_CTRL_BIT_IMMEDIATE_STOP);
	me4000_outl(dev, tmp, info->ai_context.ctrl_reg);

	/* Clear the control register */
	me4000_outl(dev, 0x0, info->ai_context.ctrl_reg);

	return 0;
}