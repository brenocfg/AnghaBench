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
struct stb0899_internal {int status; int /*<<< orphan*/  t_derot; } ;
struct stb0899_state {int /*<<< orphan*/  verbose; struct stb0899_internal internal; } ;
typedef  enum stb0899_status { ____Placeholder_stb0899_status } stb0899_status ;

/* Variables and functions */
 int CARRIEROK ; 
 int /*<<< orphan*/  CARRIER_FOUND ; 
 int /*<<< orphan*/  CFD_ON ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int NOCARRIER ; 
 int /*<<< orphan*/  STB0899_CFD ; 
 int /*<<< orphan*/  STB0899_DSTATUS ; 
 scalar_t__ STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum stb0899_status stb0899_check_carrier(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;
	u8 reg;

	msleep(internal->t_derot); /* wait for derotator ok	*/

	reg = stb0899_read_reg(state, STB0899_CFD);
	STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
	stb0899_write_reg(state, STB0899_CFD, reg);

	reg = stb0899_read_reg(state, STB0899_DSTATUS);
	dprintk(state->verbose, FE_DEBUG, 1, "--------------------> STB0899_DSTATUS=[0x%02x]", reg);
	if (STB0899_GETFIELD(CARRIER_FOUND, reg)) {
		internal->status = CARRIEROK;
		dprintk(state->verbose, FE_DEBUG, 1, "-------------> CARRIEROK !");
	} else {
		internal->status = NOCARRIER;
		dprintk(state->verbose, FE_DEBUG, 1, "-------------> NOCARRIER !");
	}

	return internal->status;
}