#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {int irq_rx_adaptive; int irq_rx_moderation; int timer_quantum_ns; size_t tx_channel_offset; TYPE_1__** channel; } ;
struct TYPE_2__ {int irq_moderation; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,int) ; 

void efx_get_irq_moderation(struct efx_nic *efx, unsigned int *tx_usecs,
			    unsigned int *rx_usecs, bool *rx_adaptive)
{
	/* We must round up when converting ticks to microseconds
	 * because we round down when converting the other way.
	 */

	*rx_adaptive = efx->irq_rx_adaptive;
	*rx_usecs = DIV_ROUND_UP(efx->irq_rx_moderation *
				 efx->timer_quantum_ns,
				 1000);

	/* If channels are shared between RX and TX, so is IRQ
	 * moderation.  Otherwise, IRQ moderation is the same for all
	 * TX channels and is not adaptive.
	 */
	if (efx->tx_channel_offset == 0)
		*tx_usecs = *rx_usecs;
	else
		*tx_usecs = DIV_ROUND_UP(
			efx->channel[efx->tx_channel_offset]->irq_moderation *
			efx->timer_quantum_ns,
			1000);
}