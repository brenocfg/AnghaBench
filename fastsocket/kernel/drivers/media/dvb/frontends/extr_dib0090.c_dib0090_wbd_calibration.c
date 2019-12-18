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
struct dib0090_state {int reset; int /*<<< orphan*/  wbd_offset; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;

/* Variables and functions */
#define  CT_TUNER_START 129 
#define  CT_TUNER_STEP_0 128 
 int EN_UHF ; 
 int /*<<< orphan*/  dib0090_read_reg (struct dib0090_state*,int) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib0090_wbd_calibration(struct dib0090_state *state, enum frontend_tune_state *tune_state)
{
	switch (*tune_state) {
	case CT_TUNER_START:
		/* WBD-mode=log, Bias=2, Gain=6, Testmode=1, en=1, WBDMUX=1 */
		dib0090_write_reg(state, 0x10, 0xdb09 | (1 << 10));
		dib0090_write_reg(state, 0x24, EN_UHF & 0x0fff);

		*tune_state = CT_TUNER_STEP_0;
		return 90;	/* wait for the WBDMUX to switch and for the ADC to sample */
	case CT_TUNER_STEP_0:
		state->wbd_offset = dib0090_read_reg(state, 0x1d);
		dprintk("WBD calibration offset = %d", state->wbd_offset);

		*tune_state = CT_TUNER_START;	/* reset done -> real tuning can now begin */
		state->reset &= ~0x2;
		break;
	default:
		break;
	}
	return 0;
}