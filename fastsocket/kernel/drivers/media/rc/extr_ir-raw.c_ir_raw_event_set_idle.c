#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rc_dev {int idle; int /*<<< orphan*/  (* s_idle ) (struct rc_dev*,int) ;TYPE_1__* raw; } ;
struct TYPE_5__ {int timeout; } ;
struct TYPE_4__ {TYPE_2__ this_ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IR_dprintk (int,char*,char*) ; 
 int /*<<< orphan*/  init_ir_raw_event (TYPE_2__*) ; 
 int /*<<< orphan*/  ir_raw_event_store (struct rc_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct rc_dev*,int) ; 

void ir_raw_event_set_idle(struct rc_dev *dev, bool idle)
{
	if (!dev->raw)
		return;

	IR_dprintk(2, "%s idle mode\n", idle ? "enter" : "leave");

	if (idle) {
		dev->raw->this_ev.timeout = true;
		ir_raw_event_store(dev, &dev->raw->this_ev);
		init_ir_raw_event(&dev->raw->this_ev);
	}

	if (dev->s_idle)
		dev->s_idle(dev, idle);

	dev->idle = idle;
}