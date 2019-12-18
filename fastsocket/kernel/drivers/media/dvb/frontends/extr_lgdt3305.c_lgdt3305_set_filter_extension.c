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
struct lgdt3305_state {int dummy; } ;
struct TYPE_3__ {int modulation; } ;
struct TYPE_4__ {TYPE_1__ vsb; } ;
struct dvb_frontend_parameters {TYPE_2__ u; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*,int) ; 
 int lgdt3305_set_reg_bit (struct lgdt3305_state*,int,int,int) ; 

__attribute__((used)) static int lgdt3305_set_filter_extension(struct lgdt3305_state *state,
					 struct dvb_frontend_parameters *param)
{
	int val;

	switch (param->u.vsb.modulation) {
	case VSB_8:
		val = 0;
		break;
	case QAM_64:
	case QAM_256:
		val = 1;
		break;
	default:
		return -EINVAL;
	}
	lg_dbg("val = %d\n", val);

	return lgdt3305_set_reg_bit(state, 0x043f, 2, val);
}