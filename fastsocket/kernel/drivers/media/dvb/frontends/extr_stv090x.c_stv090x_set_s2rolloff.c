#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct stv090x_state {TYPE_1__* internal; } ;
struct TYPE_2__ {int dev_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMOD ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  MANUAL_S2ROLLOFF_FIELD ; 
 int /*<<< orphan*/  MANUAL_SXROLLOFF_FIELD ; 
 int /*<<< orphan*/  STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int stv090x_set_s2rolloff(struct stv090x_state *state)
{
	u32 reg;

	if (state->internal->dev_ver <= 0x20) {
		/* rolloff to auto mode if DVBS2 */
		reg = STV090x_READ_DEMOD(state, DEMOD);
		STV090x_SETFIELD_Px(reg, MANUAL_SXROLLOFF_FIELD, 0x00);
		if (STV090x_WRITE_DEMOD(state, DEMOD, reg) < 0)
			goto err;
	} else {
		/* DVB-S2 rolloff to auto mode if DVBS2 */
		reg = STV090x_READ_DEMOD(state, DEMOD);
		STV090x_SETFIELD_Px(reg, MANUAL_S2ROLLOFF_FIELD, 0x00);
		if (STV090x_WRITE_DEMOD(state, DEMOD, reg) < 0)
			goto err;
	}
	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}