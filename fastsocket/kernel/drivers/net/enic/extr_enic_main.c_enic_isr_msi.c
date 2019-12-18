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
struct enic {int /*<<< orphan*/ * napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t enic_isr_msi(int irq, void *data)
{
	struct enic *enic = data;

	/* With MSI, there is no sharing of interrupts, so this is
	 * our interrupt and there is no need to ack it.  The device
	 * is not providing per-vector masking, so the OS will not
	 * write to PCI config space to mask/unmask the interrupt.
	 * We're using mask_on_assertion for MSI, so the device
	 * automatically masks the interrupt when the interrupt is
	 * generated.  Later, when exiting polling, the interrupt
	 * will be unmasked (see enic_poll).
	 *
	 * Also, the device uses the same PCIe Traffic Class (TC)
	 * for Memory Write data and MSI, so there are no ordering
	 * issues; the MSI will always arrive at the Root Complex
	 * _after_ corresponding Memory Writes (i.e. descriptor
	 * writes).
	 */

	napi_schedule(&enic->napi[0]);

	return IRQ_HANDLED;
}