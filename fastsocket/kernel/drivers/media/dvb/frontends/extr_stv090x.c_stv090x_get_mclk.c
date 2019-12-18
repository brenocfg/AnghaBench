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
typedef  int u32 ;
struct stv090x_state {struct stv090x_config* config; } ;
struct stv090x_config {int xtal; } ;

/* Variables and functions */
 int /*<<< orphan*/  SELX1RATIO_FIELD ; 
 scalar_t__ STV090x_GETFIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_NCOARSE ; 
 int /*<<< orphan*/  STV090x_SYNTCTRL ; 
 int stv090x_read_reg (struct stv090x_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stv090x_get_mclk(struct stv090x_state *state)
{
	const struct stv090x_config *config = state->config;
	u32 div, reg;
	u8 ratio;

	div = stv090x_read_reg(state, STV090x_NCOARSE);
	reg = stv090x_read_reg(state, STV090x_SYNTCTRL);
	ratio = STV090x_GETFIELD(reg, SELX1RATIO_FIELD) ? 4 : 6;

	return (div + 1) * config->xtal / ratio; /* kHz */
}