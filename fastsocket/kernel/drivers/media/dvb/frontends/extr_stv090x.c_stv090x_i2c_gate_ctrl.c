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
struct TYPE_2__ {int /*<<< orphan*/  tuner_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  I2CRPT ; 
 int /*<<< orphan*/  I2CT_ON_FIELD ; 
 int /*<<< orphan*/  STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stv090x_i2c_gate_ctrl(struct stv090x_state *state, int enable)
{
	u32 reg;

	/*
	 * NOTE! A lock is used as a FSM to control the state in which
	 * access is serialized between two tuners on the same demod.
	 * This has nothing to do with a lock to protect a critical section
	 * which may in some other cases be confused with protecting I/O
	 * access to the demodulator gate.
	 * In case of any error, the lock is unlocked and exit within the
	 * relevant operations themselves.
	 */
	if (enable)
		mutex_lock(&state->internal->tuner_lock);

	reg = STV090x_READ_DEMOD(state, I2CRPT);
	if (enable) {
		dprintk(FE_DEBUG, 1, "Enable Gate");
		STV090x_SETFIELD_Px(reg, I2CT_ON_FIELD, 1);
		if (STV090x_WRITE_DEMOD(state, I2CRPT, reg) < 0)
			goto err;

	} else {
		dprintk(FE_DEBUG, 1, "Disable Gate");
		STV090x_SETFIELD_Px(reg, I2CT_ON_FIELD, 0);
		if ((STV090x_WRITE_DEMOD(state, I2CRPT, reg)) < 0)
			goto err;
	}

	if (!enable)
		mutex_unlock(&state->internal->tuner_lock);

	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	mutex_unlock(&state->internal->tuner_lock);
	return -1;
}