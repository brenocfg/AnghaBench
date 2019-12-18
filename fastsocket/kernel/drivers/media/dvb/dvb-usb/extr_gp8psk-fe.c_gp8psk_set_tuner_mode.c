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
struct gp8psk_fe_state {int /*<<< orphan*/  d; } ;
struct dvb_frontend {struct gp8psk_fe_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_8PSK_CONFIG ; 
 int gp8psk_usb_out_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp8psk_set_tuner_mode(struct dvb_frontend *fe, int mode)
{
	struct gp8psk_fe_state *state = fe->demodulator_priv;
	return gp8psk_usb_out_op(state->d, SET_8PSK_CONFIG, mode, 0, NULL, 0);
}