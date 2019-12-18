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
struct uart_port {int /*<<< orphan*/  line; } ;
struct uart_cpm_port {int flags; TYPE_2__* sccp; TYPE_1__* smcp; } ;
struct TYPE_4__ {int /*<<< orphan*/  scc_gsmrl; int /*<<< orphan*/  scc_sccm; } ;
struct TYPE_3__ {int /*<<< orphan*/  smc_smcmr; int /*<<< orphan*/  smc_smcm; } ;

/* Variables and functions */
 int FLAG_CONSOLE ; 
 scalar_t__ IS_SMC (struct uart_cpm_port*) ; 
 int SCC_GSMRL_ENR ; 
 int SCC_GSMRL_ENT ; 
 int SMCMR_REN ; 
 int SMCMR_TEN ; 
 int SMCM_RX ; 
 int SMCM_TX ; 
 int UART_SCCM_RX ; 
 int UART_SCCM_TX ; 
 int /*<<< orphan*/  clrbits16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clrbits8 (int /*<<< orphan*/ *,int) ; 
 int cpm_uart_allocbuf (struct uart_cpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpm_uart_init_scc (struct uart_cpm_port*) ; 
 int /*<<< orphan*/  cpm_uart_init_smc (struct uart_cpm_port*) ; 
 int /*<<< orphan*/  cpm_uart_initbd (struct uart_cpm_port*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpm_uart_request_port(struct uart_port *port)
{
	struct uart_cpm_port *pinfo = (struct uart_cpm_port *)port;
	int ret;

	pr_debug("CPM uart[%d]:request port\n", port->line);

	if (pinfo->flags & FLAG_CONSOLE)
		return 0;

	if (IS_SMC(pinfo)) {
		clrbits8(&pinfo->smcp->smc_smcm, SMCM_RX | SMCM_TX);
		clrbits16(&pinfo->smcp->smc_smcmr, SMCMR_REN | SMCMR_TEN);
	} else {
		clrbits16(&pinfo->sccp->scc_sccm, UART_SCCM_TX | UART_SCCM_RX);
		clrbits32(&pinfo->sccp->scc_gsmrl, SCC_GSMRL_ENR | SCC_GSMRL_ENT);
	}

	ret = cpm_uart_allocbuf(pinfo, 0);

	if (ret)
		return ret;

	cpm_uart_initbd(pinfo);
	if (IS_SMC(pinfo))
		cpm_uart_init_smc(pinfo);
	else
		cpm_uart_init_scc(pinfo);

	return 0;
}