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
struct scc_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDR_TX_INT_ENAB ; 
 int /*<<< orphan*/  INT_AND_DMA_REG ; 
 int /*<<< orphan*/  SCC_ACCESS_INIT (struct scc_port*) ; 
 int /*<<< orphan*/  SCCmod (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  scc_tx_int (int /*<<< orphan*/ ,struct scc_port*) ; 

__attribute__((used)) static void scc_enable_tx_interrupts(void *ptr)
{
	struct scc_port *port = ptr;
	unsigned long	flags;
	SCC_ACCESS_INIT(port);

	local_irq_save(flags);
	SCCmod(INT_AND_DMA_REG, 0xff, IDR_TX_INT_ENAB);
	/* restart the transmitter */
	scc_tx_int (0, port);
	local_irq_restore(flags);
}