#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  line; } ;
struct uart_cpm_port {int flags; TYPE_2__* sccp; TYPE_1__* smcp; } ;
struct TYPE_4__ {int /*<<< orphan*/  scc_gsmrl; int /*<<< orphan*/  scc_sccm; } ;
struct TYPE_3__ {int /*<<< orphan*/  smc_smcmr; int /*<<< orphan*/  smc_smcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPM_CR_INIT_TRX ; 
 int FLAG_CONSOLE ; 
 scalar_t__ IS_SMC (struct uart_cpm_port*) ; 
 int SCC_GSMRL_ENR ; 
 int SCC_GSMRL_ENT ; 
 int SMCMR_REN ; 
 int SMCMR_TEN ; 
 int /*<<< orphan*/  SMCM_RX ; 
 int UART_SCCM_RX ; 
 int /*<<< orphan*/  clrbits16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clrbits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpm_line_cr_cmd (struct uart_cpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpm_uart_int ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 
 int /*<<< orphan*/  setbits16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setbits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpm_uart_startup(struct uart_port *port)
{
	int retval;
	struct uart_cpm_port *pinfo = (struct uart_cpm_port *)port;

	pr_debug("CPM uart[%d]:startup\n", port->line);

	/* If the port is not the console, make sure rx is disabled. */
	if (!(pinfo->flags & FLAG_CONSOLE)) {
		/* Disable UART rx */
		if (IS_SMC(pinfo)) {
			clrbits16(&pinfo->smcp->smc_smcmr, SMCMR_REN);
			clrbits8(&pinfo->smcp->smc_smcm, SMCM_RX);
		} else {
			clrbits32(&pinfo->sccp->scc_gsmrl, SCC_GSMRL_ENR);
			clrbits16(&pinfo->sccp->scc_sccm, UART_SCCM_RX);
		}
		cpm_line_cr_cmd(pinfo, CPM_CR_INIT_TRX);
	}
	/* Install interrupt handler. */
	retval = request_irq(port->irq, cpm_uart_int, 0, "cpm_uart", port);
	if (retval)
		return retval;

	/* Startup rx-int */
	if (IS_SMC(pinfo)) {
		setbits8(&pinfo->smcp->smc_smcm, SMCM_RX);
		setbits16(&pinfo->smcp->smc_smcmr, (SMCMR_REN | SMCMR_TEN));
	} else {
		setbits16(&pinfo->sccp->scc_sccm, UART_SCCM_RX);
		setbits32(&pinfo->sccp->scc_gsmrl, (SCC_GSMRL_ENR | SCC_GSMRL_ENT));
	}

	return 0;
}