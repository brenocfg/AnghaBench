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
struct stv0299_state {scalar_t__ initialised; } ;
struct dvb_frontend {struct stv0299_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0299_writeregI (struct stv0299_state*,int,int) ; 

__attribute__((used)) static int stv0299_sleep(struct dvb_frontend* fe)
{
	struct stv0299_state* state = fe->demodulator_priv;

	stv0299_writeregI(state, 0x02, 0x80);
	state->initialised = 0;

	return 0;
}