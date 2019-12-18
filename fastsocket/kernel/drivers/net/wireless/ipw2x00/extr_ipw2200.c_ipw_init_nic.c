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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_BIT_INT_HOST_SRAM_READ_INT_REGISTER ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_TRACE (char*) ; 
 int /*<<< orphan*/  IPW_GP_CNTRL_BIT_CLOCK_READY ; 
 int /*<<< orphan*/  IPW_GP_CNTRL_BIT_INIT_DONE ; 
 int /*<<< orphan*/  IPW_GP_CNTRL_RW ; 
 int /*<<< orphan*/  IPW_READ_INT_REGISTER ; 
 int /*<<< orphan*/  IPW_RESET_REG ; 
 int /*<<< orphan*/  IPW_RESET_REG_SW_RESET ; 
 int ipw_poll_bit (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipw_set_bit (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ipw_init_nic(struct ipw_priv *priv)
{
	int rc;

	IPW_DEBUG_TRACE(">>\n");
	/* reset */
	/*prvHwInitNic */
	/* set "initialization complete" bit to move adapter to D0 state */
	ipw_set_bit(priv, IPW_GP_CNTRL_RW, IPW_GP_CNTRL_BIT_INIT_DONE);

	/* low-level PLL activation */
	ipw_write32(priv, IPW_READ_INT_REGISTER,
		    IPW_BIT_INT_HOST_SRAM_READ_INT_REGISTER);

	/* wait for clock stabilization */
	rc = ipw_poll_bit(priv, IPW_GP_CNTRL_RW,
			  IPW_GP_CNTRL_BIT_CLOCK_READY, 250);
	if (rc < 0)
		IPW_DEBUG_INFO("FAILED wait for clock stablization\n");

	/* assert SW reset */
	ipw_set_bit(priv, IPW_RESET_REG, IPW_RESET_REG_SW_RESET);

	udelay(10);

	/* set "initialization complete" bit to move adapter to D0 state */
	ipw_set_bit(priv, IPW_GP_CNTRL_RW, IPW_GP_CNTRL_BIT_INIT_DONE);

	IPW_DEBUG_TRACE(">>\n");
	return 0;
}