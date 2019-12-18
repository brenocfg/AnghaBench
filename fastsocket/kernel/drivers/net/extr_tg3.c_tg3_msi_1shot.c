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
struct tg3_napi {size_t rx_rcb_ptr; int /*<<< orphan*/  napi; int /*<<< orphan*/ * rx_rcb; int /*<<< orphan*/ * hw_status; struct tg3* tp; } ;
struct tg3 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_irq_sync (struct tg3*) ; 

__attribute__((used)) static irqreturn_t tg3_msi_1shot(int irq, void *dev_id)
{
	struct tg3_napi *tnapi = dev_id;
	struct tg3 *tp = tnapi->tp;

	prefetch(tnapi->hw_status);
	if (tnapi->rx_rcb)
		prefetch(&tnapi->rx_rcb[tnapi->rx_rcb_ptr]);

	if (likely(!tg3_irq_sync(tp)))
		napi_schedule(&tnapi->napi);

	return IRQ_HANDLED;
}