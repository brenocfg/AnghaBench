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
struct dvb_frontend_parameters {int dummy; } ;
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; } ;
struct dtt200u_fe_state {int /*<<< orphan*/  fep; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct dvb_frontend_parameters*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dtt200u_fe_get_frontend(struct dvb_frontend* fe,
				  struct dvb_frontend_parameters *fep)
{
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	memcpy(fep,&state->fep,sizeof(struct dvb_frontend_parameters));
	return 0;
}