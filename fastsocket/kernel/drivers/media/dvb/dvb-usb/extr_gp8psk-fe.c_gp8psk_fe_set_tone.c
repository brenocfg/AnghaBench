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
typedef  scalar_t__ fe_sec_tone_mode_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SEC_TONE_ON ; 
 int /*<<< orphan*/  SET_22KHZ_TONE ; 
 scalar_t__ gp8psk_usb_out_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp8psk_fe_set_tone (struct dvb_frontend* fe, fe_sec_tone_mode_t tone)
{
	struct gp8psk_fe_state* state = fe->demodulator_priv;

	if (gp8psk_usb_out_op(state->d,SET_22KHZ_TONE,
		 (tone == SEC_TONE_ON), 0, NULL, 0)) {
		return -EINVAL;
	}
	return 0;
}