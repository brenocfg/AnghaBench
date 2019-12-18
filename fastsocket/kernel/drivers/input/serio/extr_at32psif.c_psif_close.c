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
struct psif {int /*<<< orphan*/  pclk; scalar_t__ open; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  CR_RXDIS ; 
 int /*<<< orphan*/  CR_TXDIS ; 
 int /*<<< orphan*/  IDR ; 
 unsigned long PSIF_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psif_writel (struct psif*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void psif_close(struct serio *io)
{
	struct psif *psif = io->port_data;

	psif->open = 0;

	psif_writel(psif, IDR, ~0UL);
	psif_writel(psif, CR, PSIF_BIT(CR_TXDIS) | PSIF_BIT(CR_RXDIS));

	clk_disable(psif->pclk);
}