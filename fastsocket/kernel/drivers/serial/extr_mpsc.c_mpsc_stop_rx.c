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
struct uart_port {int /*<<< orphan*/  line; } ;
struct mpsc_port_info {int MPSC_CHR_2_m; scalar_t__ mpsc_base; scalar_t__ mirror_regs; } ;

/* Variables and functions */
 scalar_t__ MPSC_CHR_2 ; 
 int MPSC_CHR_2_RA ; 
 int /*<<< orphan*/  SDMA_SDCM_AR ; 
 int /*<<< orphan*/  mpsc_sdma_cmd (struct mpsc_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mpsc_stop_rx(struct uart_port *port)
{
	struct mpsc_port_info *pi = (struct mpsc_port_info *)port;

	pr_debug("mpsc_stop_rx[%d]: Stopping...\n", port->line);

	if (pi->mirror_regs) {
		writel(pi->MPSC_CHR_2_m | MPSC_CHR_2_RA,
				pi->mpsc_base + MPSC_CHR_2);
		/* Erratum prevents reading CHR_2 so just delay for a while */
		udelay(100);
	} else {
		writel(readl(pi->mpsc_base + MPSC_CHR_2) | MPSC_CHR_2_RA,
				pi->mpsc_base + MPSC_CHR_2);

		while (readl(pi->mpsc_base + MPSC_CHR_2) & MPSC_CHR_2_RA)
			udelay(10);
	}

	mpsc_sdma_cmd(pi, SDMA_SDCM_AR);
}