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
struct mixart_mgr {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXART_ALLOW_OUTBOUND_DOORBELL ; 
 int /*<<< orphan*/  MIXART_MEM (struct mixart_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIXART_PCI_OMIMR_OFFSET ; 
 int /*<<< orphan*/  MIXART_REG (struct mixart_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_AGENT_RSC_PROTECTION ; 
 int /*<<< orphan*/  MSG_HOST_RSC_PROTECTION ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_mixart_init_mailbox(struct mixart_mgr *mgr)
{
	writel( 0, MIXART_MEM( mgr, MSG_HOST_RSC_PROTECTION ) );
	writel( 0, MIXART_MEM( mgr, MSG_AGENT_RSC_PROTECTION ) );

	/* allow outbound messagebox to generate interrupts */
	if(mgr->irq >= 0) {
		writel_le( MIXART_ALLOW_OUTBOUND_DOORBELL, MIXART_REG( mgr, MIXART_PCI_OMIMR_OFFSET));
	}
	return;
}