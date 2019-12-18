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
struct scc_channel {int /*<<< orphan*/  irq; int /*<<< orphan*/ * tx_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_start_maxkeyup (struct scc_channel*) ; 
 int /*<<< orphan*/  scc_txint (struct scc_channel*) ; 

__attribute__((used)) static void t_txdelay(unsigned long channel)
{
	struct scc_channel *scc = (struct scc_channel *) channel;

	scc_start_maxkeyup(scc);

	if (scc->tx_buff == NULL)
	{
		disable_irq(scc->irq);
		scc_txint(scc);	
		enable_irq(scc->irq);
	}
}