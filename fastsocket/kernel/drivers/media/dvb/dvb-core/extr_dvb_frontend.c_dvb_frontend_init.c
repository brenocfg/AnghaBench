#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* init ) (struct dvb_frontend*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_2__ tuner_ops; int /*<<< orphan*/  (* init ) (struct dvb_frontend*) ;TYPE_1__ info; } ;
struct dvb_frontend {TYPE_3__ ops; int /*<<< orphan*/  id; TYPE_4__* dvb; } ;
struct TYPE_8__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub4 (struct dvb_frontend*,int) ; 

__attribute__((used)) static void dvb_frontend_init(struct dvb_frontend *fe)
{
	dprintk ("DVB: initialising adapter %i frontend %i (%s)...\n",
		 fe->dvb->num,
		 fe->id,
		 fe->ops.info.name);

	if (fe->ops.init)
		fe->ops.init(fe);
	if (fe->ops.tuner_ops.init) {
		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		fe->ops.tuner_ops.init(fe);
		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	}
}