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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_tuner_ops {int /*<<< orphan*/  (* set_analog_params ) (TYPE_3__*,struct analog_parameters*) ;} ;
struct cx231xx {TYPE_2__* dvb; int /*<<< orphan*/  norm; } ;
struct analog_parameters {scalar_t__ mode; int /*<<< orphan*/  std; int /*<<< orphan*/  frequency; } ;
struct TYPE_4__ {struct dvb_tuner_ops tuner_ops; } ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct TYPE_5__ {TYPE_3__* frontend; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct analog_parameters*) ; 

int cx231xx_set_analog_freq(struct cx231xx *dev, u32 freq)
{
	int status = 0;

	if ((dev->dvb != NULL) && (dev->dvb->frontend != NULL)) {

		struct dvb_tuner_ops *dops = &dev->dvb->frontend->ops.tuner_ops;

		if (dops->set_analog_params != NULL) {
			struct analog_parameters params;

			params.frequency = freq;
			params.std = dev->norm;
			params.mode = 0;	/* 0- Air; 1 - cable */
			/*params.audmode = ;       */

			/* Set the analog parameters to set the frequency */
			dops->set_analog_params(dev->dvb->frontend, &params);
		}

	}

	return status;
}