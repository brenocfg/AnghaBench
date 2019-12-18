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
struct tda10021_state {int dummy; } ;
struct dvb_frontend {struct tda10021_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tda10021_writereg (struct tda10021_state*,int,int) ; 

__attribute__((used)) static int tda10021_sleep(struct dvb_frontend* fe)
{
	struct tda10021_state* state = fe->demodulator_priv;

	_tda10021_writereg (state, 0x1b, 0x02);  /* pdown ADC */
	_tda10021_writereg (state, 0x00, 0x80);  /* standby */

	return 0;
}