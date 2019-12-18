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
struct ves1820_state {int dummy; } ;
struct dvb_frontend {struct ves1820_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ves1820_writereg (struct ves1820_state*,int,int) ; 

__attribute__((used)) static int ves1820_sleep(struct dvb_frontend* fe)
{
	struct ves1820_state* state = fe->demodulator_priv;

	ves1820_writereg(state, 0x1b, 0x02);	/* pdown ADC */
	ves1820_writereg(state, 0x00, 0x80);	/* standby */

	return 0;
}