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
struct uart_pmac_port {int /*<<< orphan*/  port_type; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_MODEM_ENABLE ; 
 int /*<<< orphan*/  PMAC_FTR_SCC_ENABLE ; 
 scalar_t__ ZS_IS_INTMODEM (struct uart_pmac_port*) ; 
 int pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmz_debug (char*,int) ; 

__attribute__((used)) static int pmz_set_scc_power(struct uart_pmac_port *uap, int state)
{
	int delay = 0;
	int rc;

	if (state) {
		rc = pmac_call_feature(
			PMAC_FTR_SCC_ENABLE, uap->node, uap->port_type, 1);
		pmz_debug("port power on result: %d\n", rc);
		if (ZS_IS_INTMODEM(uap)) {
			rc = pmac_call_feature(
				PMAC_FTR_MODEM_ENABLE, uap->node, 0, 1);
			delay = 2500;	/* wait for 2.5s before using */
			pmz_debug("modem power result: %d\n", rc);
		}
	} else {
		/* TODO: Make that depend on a timer, don't power down
		 * immediately
		 */
		if (ZS_IS_INTMODEM(uap)) {
			rc = pmac_call_feature(
				PMAC_FTR_MODEM_ENABLE, uap->node, 0, 0);
			pmz_debug("port power off result: %d\n", rc);
		}
		pmac_call_feature(PMAC_FTR_SCC_ENABLE, uap->node, uap->port_type, 0);
	}
	return delay;
}