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
typedef  scalar_t__ u8 ;
struct jdvbt90502_state {int dummy; } ;
struct dvb_frontend {struct jdvbt90502_state* demodulator_priv; } ;

/* Variables and functions */
 int jdvbt90502_single_reg_write (struct jdvbt90502_state*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int _jdvbt90502_write(struct dvb_frontend *fe, u8 *buf, int len)
{
	struct jdvbt90502_state *state = fe->demodulator_priv;
	int err, i;
	for (i = 0; i < len - 1; i++) {
		err = jdvbt90502_single_reg_write(state,
						  buf[0] + i, buf[i + 1]);
		if (err)
			return err;
	}

	return 0;
}