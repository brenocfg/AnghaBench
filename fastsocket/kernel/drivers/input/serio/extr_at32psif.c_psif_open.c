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
struct serio {struct psif* port_data; } ;
struct psif {int open; int /*<<< orphan*/  pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  CR_RXEN ; 
 int /*<<< orphan*/  CR_TXEN ; 
 int /*<<< orphan*/  IER ; 
 int PSIF_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXRDY ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psif_writel (struct psif*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int psif_open(struct serio *io)
{
	struct psif *psif = io->port_data;
	int retval;

	retval = clk_enable(psif->pclk);
	if (retval)
		goto out;

	psif_writel(psif, CR, PSIF_BIT(CR_TXEN) | PSIF_BIT(CR_RXEN));
	psif_writel(psif, IER, PSIF_BIT(RXRDY));

	psif->open = 1;
out:
	return retval;
}