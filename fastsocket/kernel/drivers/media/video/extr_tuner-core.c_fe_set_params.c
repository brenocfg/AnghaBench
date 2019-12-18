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
struct tuner {int dummy; } ;
struct dvb_tuner_ops {int /*<<< orphan*/  (* set_analog_params ) (struct dvb_frontend*,struct analog_parameters*) ;} ;
struct TYPE_2__ {struct dvb_tuner_ops tuner_ops; } ;
struct dvb_frontend {struct tuner* analog_demod_priv; TYPE_1__ ops; } ;
struct analog_parameters {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct analog_parameters*) ; 
 int /*<<< orphan*/  tuner_warn (char*) ; 

__attribute__((used)) static void fe_set_params(struct dvb_frontend *fe,
			  struct analog_parameters *params)
{
	struct dvb_tuner_ops *fe_tuner_ops = &fe->ops.tuner_ops;
	struct tuner *t = fe->analog_demod_priv;

	if (NULL == fe_tuner_ops->set_analog_params) {
		tuner_warn("Tuner frontend module has no way to set freq\n");
		return;
	}
	fe_tuner_ops->set_analog_params(fe, params);
}