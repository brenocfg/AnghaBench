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
struct s921_state {int /*<<< orphan*/  dev; } ;
struct s921_isdb_t_tune_params {int /*<<< orphan*/  frequency; } ;
struct s921_isdb_t_transmission_mode_params {int /*<<< orphan*/  frequency; } ;
struct dvb_frontend_parameters {int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {scalar_t__ demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDB_T_CMD_SET_PARAM ; 
 int /*<<< orphan*/  ISDB_T_CMD_TUNE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  s921_isdb_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct s921_isdb_t_tune_params*) ; 

__attribute__((used)) static int s921_set_parameters(struct dvb_frontend *fe, struct dvb_frontend_parameters *param) {
	struct s921_state *state = (struct s921_state *)fe->demodulator_priv;
	struct s921_isdb_t_transmission_mode_params params;
	struct s921_isdb_t_tune_params tune_params;

	tune_params.frequency = param->frequency;
	s921_isdb_cmd(&state->dev, ISDB_T_CMD_SET_PARAM, &params);
	s921_isdb_cmd(&state->dev, ISDB_T_CMD_TUNE, &tune_params);
	mdelay(100);
	return 0;
}