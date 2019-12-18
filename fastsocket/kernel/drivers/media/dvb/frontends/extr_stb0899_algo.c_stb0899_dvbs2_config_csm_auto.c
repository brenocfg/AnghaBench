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
typedef  int /*<<< orphan*/  u32 ;
struct stb0899_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSM_AUTO_PARAM ; 
 int /*<<< orphan*/  CSM_CNTRL1 ; 
 int /*<<< orphan*/  STB0899_BASE_CSM_CNTRL1 ; 
 int /*<<< orphan*/  STB0899_OFF0_CSM_CNTRL1 ; 
 int /*<<< orphan*/  STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stb0899_write_s2reg (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stb0899_dvbs2_config_csm_auto(struct stb0899_state *state)
{
	u32 reg;

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL1);
	STB0899_SETFIELD_VAL(CSM_AUTO_PARAM, reg, 1);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL1, STB0899_OFF0_CSM_CNTRL1, reg);
}