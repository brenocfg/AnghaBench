#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct smc_regs {int smc_smcm; int smc_smcmr; } ;
struct serial_state {int smc_scc_num; int /*<<< orphan*/  irq; } ;
struct TYPE_8__ {int low; } ;
struct TYPE_9__ {TYPE_1__ w; } ;
struct scc_regs {int scc_sccm; TYPE_2__ scc_gsmr; } ;
struct TYPE_11__ {TYPE_3__* tty; } ;
struct TYPE_12__ {int flags; TYPE_4__ port; int /*<<< orphan*/  line; struct serial_state* state; } ;
typedef  TYPE_5__ ser_info_t ;
struct TYPE_13__ {struct smc_regs* smc_regs; struct scc_regs* scc_regs; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int CONFIG_SERIAL_CONSOLE_PORT ; 
 int NUM_IS_SCC ; 
 int PORT_NUM (int) ; 
 int SCC_GSMRL_ENR ; 
 int SCC_GSMRL_ENT ; 
 int SMCMR_REN ; 
 int SMCMR_TEN ; 
 int SMCM_RX ; 
 int SMCM_TX ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int UART_SCCM_RX ; 
 int UART_SCCM_TX ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_7__* pquicc ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct serial_state* rs_table ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shutdown(ser_info_t *info)
{
	unsigned long	flags;
	struct serial_state *state;
	int		idx;
	volatile struct smc_regs	*smcp;
	volatile struct scc_regs	*sccp;

	if (!(info->flags & ASYNC_INITIALIZED))
		return;

	state = info->state;

#ifdef SERIAL_DEBUG_OPEN
	printk("Shutting down serial port %d (irq %d)....", info->line,
	       state->irq);
#endif
	
	local_irq_save(flags);

	idx = PORT_NUM(state->smc_scc_num);
	if (state->smc_scc_num & NUM_IS_SCC) {
		sccp = &pquicc->scc_regs[idx];
		sccp->scc_gsmr.w.low &= ~(SCC_GSMRL_ENR | SCC_GSMRL_ENT);
#ifdef CONFIG_SERIAL_CONSOLE
		/* We can't disable the transmitter if this is the
		 * system console.
		 */
		if ((state - rs_table) != CONFIG_SERIAL_CONSOLE_PORT)
#endif
		sccp->scc_sccm &= ~(UART_SCCM_TX | UART_SCCM_RX);
	} else {
		smcp = &pquicc->smc_regs[idx];

		/* Disable interrupts and I/O.
		 */
		smcp->smc_smcm &= ~(SMCM_RX | SMCM_TX);
#ifdef CONFIG_SERIAL_CONSOLE
		/* We can't disable the transmitter if this is the
		 * system console.
		 */
		if ((state - rs_table) != CONFIG_SERIAL_CONSOLE_PORT)
#endif
			smcp->smc_smcmr &= ~(SMCMR_REN | SMCMR_TEN);
	}
	
	if (info->port.tty)
		set_bit(TTY_IO_ERROR, &info->port.tty->flags);

	info->flags &= ~ASYNC_INITIALIZED;
	local_irq_restore(flags);
}