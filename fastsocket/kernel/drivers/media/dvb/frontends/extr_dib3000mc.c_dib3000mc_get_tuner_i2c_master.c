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
struct i2c_adapter {int dummy; } ;
struct dvb_frontend {struct dib3000mc_state* demodulator_priv; } ;
struct dib3000mc_state {int /*<<< orphan*/  i2c_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_TUNER ; 
 struct i2c_adapter* dibx000_get_i2c_adapter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct i2c_adapter * dib3000mc_get_tuner_i2c_master(struct dvb_frontend *demod, int gating)
{
	struct dib3000mc_state *st = demod->demodulator_priv;
	return dibx000_get_i2c_adapter(&st->i2c_master, DIBX000_I2C_INTERFACE_TUNER, gating);
}