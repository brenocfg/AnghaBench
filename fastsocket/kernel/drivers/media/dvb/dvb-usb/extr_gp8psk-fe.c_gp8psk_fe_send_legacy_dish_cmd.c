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
typedef  int u8 ;
struct gp8psk_fe_state {int /*<<< orphan*/  d; } ;
struct dvb_frontend {struct gp8psk_fe_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SET_DN_SWITCH ; 
 int /*<<< orphan*/  SET_LNB_VOLTAGE ; 
 scalar_t__ gp8psk_usb_out_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp8psk_fe_send_legacy_dish_cmd (struct dvb_frontend* fe, unsigned long sw_cmd)
{
	struct gp8psk_fe_state* state = fe->demodulator_priv;
	u8 cmd = sw_cmd & 0x7f;

	if (gp8psk_usb_out_op(state->d,SET_DN_SWITCH, cmd, 0,
			NULL, 0)) {
		return -EINVAL;
	}
	if (gp8psk_usb_out_op(state->d,SET_LNB_VOLTAGE, !!(sw_cmd & 0x80),
			0, NULL, 0)) {
		return -EINVAL;
	}

	return 0;
}