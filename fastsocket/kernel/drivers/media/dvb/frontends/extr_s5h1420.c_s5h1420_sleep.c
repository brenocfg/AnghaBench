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
struct s5h1420_state {int CON_1_val; } ;
struct dvb_frontend {struct s5h1420_state* demodulator_priv; } ;

/* Variables and functions */
 int s5h1420_writereg (struct s5h1420_state*,int,int) ; 

__attribute__((used)) static int s5h1420_sleep(struct dvb_frontend* fe)
{
	struct s5h1420_state* state = fe->demodulator_priv;
	state->CON_1_val = 0x12;
	return s5h1420_writereg(state, 0x02, state->CON_1_val);
}