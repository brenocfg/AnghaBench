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
typedef  int /*<<< orphan*/  u8 ;
struct stv0288_state {int dummy; } ;
struct dvb_frontend {struct stv0288_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int stv0288_writeregI (struct stv0288_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0288_write(struct dvb_frontend *fe, u8 *buf, int len)
{
	struct stv0288_state *state = fe->demodulator_priv;

	if (len != 2)
		return -EINVAL;

	return stv0288_writeregI(state, buf[0], buf[1]);
}