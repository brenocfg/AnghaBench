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
typedef  int /*<<< orphan*/  u32 ;
struct dvbt_get_status_msg {int /*<<< orphan*/  uncorrected_block_count; } ;
struct dvb_frontend {struct cinergyt2_fe_state* demodulator_priv; } ;
struct cinergyt2_fe_state {int /*<<< orphan*/  d; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CINERGYT2_EP1_GET_TUNER_STATUS ; 
 int dvb_usb_generic_rw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cinergyt2_fe_read_unc_blocks(struct dvb_frontend *fe, u32 *unc)
{
	struct cinergyt2_fe_state *state = fe->demodulator_priv;
	struct dvbt_get_status_msg status;
	u8 cmd[] = { CINERGYT2_EP1_GET_TUNER_STATUS };
	int ret;

	ret = dvb_usb_generic_rw(state->d, cmd, sizeof(cmd), (u8 *)&status,
				sizeof(status), 0);
	if (ret < 0) {
		err("cinergyt2_fe_read_unc_blocks() Failed! (Error=%d)\n",
			ret);
		return ret;
	}
	*unc = le32_to_cpu(status.uncorrected_block_count);
	return 0;
}