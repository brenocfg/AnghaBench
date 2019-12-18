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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int ai_cmd2; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/ * inttrig; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_Command_2_Register ; 
 int AI_START1_Pulse ; 
 int EINVAL ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ai_inttrig(struct comedi_device *dev, struct comedi_subdevice *s,
			 unsigned int trignum)
{
	if (trignum != 0)
		return -EINVAL;

	devpriv->stc_writew(dev, AI_START1_Pulse | devpriv->ai_cmd2,
			    AI_Command_2_Register);
	s->async->inttrig = NULL;

	return 1;
}