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
struct stb0899_state {int /*<<< orphan*/  verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFGPDELSTATUS_LOCK ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  STB0899_CFGPDELSTATUS1 ; 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb0899_dvbs2_get_data_lock(struct stb0899_state *state, int timeout)
{
	int time = 0, lock = 0;
	u8 reg;

	while ((!lock) && (time < timeout)) {
		reg = stb0899_read_reg(state, STB0899_CFGPDELSTATUS1);
		dprintk(state->verbose, FE_DEBUG, 1, "---------> CFGPDELSTATUS=[0x%02x]", reg);
		lock = STB0899_GETFIELD(CFGPDELSTATUS_LOCK, reg);
		time++;
	}

	return lock;
}