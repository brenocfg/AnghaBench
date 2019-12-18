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
struct tg3_napi {struct tg3_hw_status* hw_status; struct tg3* tp; } ;
struct tg3_hw_status {int status; } ;
struct tg3 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int PCISTATE_INT_NOT_ACTIVE ; 
 int SD_STATUS_UPDATED ; 
 int /*<<< orphan*/  TG3PCI_PCISTATE ; 
 int /*<<< orphan*/  tg3_disable_ints (struct tg3*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tg3_test_isr(int irq, void *dev_id)
{
	struct tg3_napi *tnapi = dev_id;
	struct tg3 *tp = tnapi->tp;
	struct tg3_hw_status *sblk = tnapi->hw_status;

	if ((sblk->status & SD_STATUS_UPDATED) ||
	    !(tr32(TG3PCI_PCISTATE) & PCISTATE_INT_NOT_ACTIVE)) {
		tg3_disable_ints(tp);
		return IRQ_RETVAL(1);
	}
	return IRQ_RETVAL(0);
}