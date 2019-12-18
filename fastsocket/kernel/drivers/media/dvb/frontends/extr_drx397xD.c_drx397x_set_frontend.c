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
struct dvb_frontend_parameters {int dummy; } ;
struct dvb_frontend {struct drx397xD_state* demodulator_priv; } ;
struct TYPE_2__ {int s20d24; } ;
struct drx397xD_state {TYPE_1__ config; } ;

/* Variables and functions */
 int drx_tune (struct drx397xD_state*,struct dvb_frontend_parameters*) ; 

__attribute__((used)) static int drx397x_set_frontend(struct dvb_frontend *fe,
				struct dvb_frontend_parameters *params)
{
	struct drx397xD_state *s = fe->demodulator_priv;

	s->config.s20d24 = 1;

	return drx_tune(s, params);
}