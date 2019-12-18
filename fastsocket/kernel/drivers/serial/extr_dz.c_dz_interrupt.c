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
typedef  int u16 ;
struct dz_port {int dummy; } ;
struct dz_mux {struct dz_port* dport; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DZ_CSR ; 
 int DZ_RDONE ; 
 int DZ_RIE ; 
 int DZ_TIE ; 
 int DZ_TRDY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int dz_in (struct dz_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dz_receive_chars (struct dz_mux*) ; 
 int /*<<< orphan*/  dz_transmit_chars (struct dz_mux*) ; 

__attribute__((used)) static irqreturn_t dz_interrupt(int irq, void *dev_id)
{
	struct dz_mux *mux = dev_id;
	struct dz_port *dport = &mux->dport[0];
	u16 status;

	/* get the reason why we just got an irq */
	status = dz_in(dport, DZ_CSR);

	if ((status & (DZ_RDONE | DZ_RIE)) == (DZ_RDONE | DZ_RIE))
		dz_receive_chars(mux);

	if ((status & (DZ_TRDY | DZ_TIE)) == (DZ_TRDY | DZ_TIE))
		dz_transmit_chars(mux);

	return IRQ_HANDLED;
}