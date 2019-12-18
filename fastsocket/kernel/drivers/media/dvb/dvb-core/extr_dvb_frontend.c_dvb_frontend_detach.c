#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* release ) (struct dvb_frontend*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* release ) (struct dvb_frontend*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct dvb_frontend*) ;TYPE_1__ analog_ops; TYPE_3__ tuner_ops; int /*<<< orphan*/  (* release_sec ) (struct dvb_frontend*) ;} ;
struct dvb_frontend {TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub4 (struct dvb_frontend*) ; 

void dvb_frontend_detach(struct dvb_frontend* fe)
{
	if (fe->ops.release_sec)
		fe->ops.release_sec(fe);
	if (fe->ops.tuner_ops.release)
		fe->ops.tuner_ops.release(fe);
	if (fe->ops.analog_ops.release)
		fe->ops.analog_ops.release(fe);
	if (fe->ops.release)
		fe->ops.release(fe);
}