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
struct stb0899_params {int srate; } ;
struct stb0899_internal {int status; } ;
struct stb0899_state {int /*<<< orphan*/  verbose; struct stb0899_params params; struct stb0899_internal internal; } ;
typedef  enum stb0899_status { ____Placeholder_stb0899_status } stb0899_status ;

/* Variables and functions */
 int DATAOK ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FRESACS ; 
 int NODATA ; 
 int /*<<< orphan*/  STB0899_DSTATUS2 ; 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  STB0899_TSTRES ; 
 int /*<<< orphan*/  STB0899_VSTATUS ; 
 int /*<<< orphan*/  VSTATUS_END_LOOPVIT ; 
 int /*<<< orphan*/  VSTATUS_LOCKEDVIT ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum stb0899_status stb0899_check_data(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;
	struct stb0899_params *params = &state->params;

	int lock = 0, index = 0, dataTime = 500, loop;
	u8 reg;

	internal->status = NODATA;

	/* RESET FEC	*/
	reg = stb0899_read_reg(state, STB0899_TSTRES);
	STB0899_SETFIELD_VAL(FRESACS, reg, 1);
	stb0899_write_reg(state, STB0899_TSTRES, reg);
	msleep(1);
	reg = stb0899_read_reg(state, STB0899_TSTRES);
	STB0899_SETFIELD_VAL(FRESACS, reg, 0);
	stb0899_write_reg(state, STB0899_TSTRES, reg);

	if (params->srate <= 2000000)
		dataTime = 2000;
	else if (params->srate <= 5000000)
		dataTime = 1500;
	else if (params->srate <= 15000000)
		dataTime = 1000;
	else
		dataTime = 500;

	stb0899_write_reg(state, STB0899_DSTATUS2, 0x00); /* force search loop	*/
	while (1) {
		/* WARNING! VIT LOCKED has to be tested before VIT_END_LOOOP	*/
		reg = stb0899_read_reg(state, STB0899_VSTATUS);
		lock = STB0899_GETFIELD(VSTATUS_LOCKEDVIT, reg);
		loop = STB0899_GETFIELD(VSTATUS_END_LOOPVIT, reg);

		if (lock || loop || (index > dataTime))
			break;
		index++;
	}

	if (lock) {	/* DATA LOCK indicator	*/
		internal->status = DATAOK;
		dprintk(state->verbose, FE_DEBUG, 1, "-----------------> DATA OK !");
	}

	return internal->status;
}