#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct lgdt3305_state {int dummy; } ;
struct TYPE_3__ {int modulation; } ;
struct TYPE_4__ {TYPE_1__ vsb; } ;
struct dvb_frontend_parameters {TYPE_2__ u; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LGDT3305_GEN_CTRL_1 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*) ; 
 scalar_t__ lg_fail (int) ; 
 int lgdt3305_read_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int*) ; 
 int lgdt3305_write_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lgdt3305_set_modulation(struct lgdt3305_state *state,
				   struct dvb_frontend_parameters *param)
{
	u8 opermode;
	int ret;

	lg_dbg("\n");

	ret = lgdt3305_read_reg(state, LGDT3305_GEN_CTRL_1, &opermode);
	if (lg_fail(ret))
		goto fail;

	opermode &= ~0x03;

	switch (param->u.vsb.modulation) {
	case VSB_8:
		opermode |= 0x03;
		break;
	case QAM_64:
		opermode |= 0x00;
		break;
	case QAM_256:
		opermode |= 0x01;
		break;
	default:
		return -EINVAL;
	}
	ret = lgdt3305_write_reg(state, LGDT3305_GEN_CTRL_1, opermode);
fail:
	return ret;
}