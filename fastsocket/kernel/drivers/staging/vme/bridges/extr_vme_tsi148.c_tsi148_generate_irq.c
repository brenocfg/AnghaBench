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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_VICR ; 
 int* TSI148_LCSR_VICR_IRQL ; 
 int TSI148_LCSR_VICR_STID_M ; 
 int /*<<< orphan*/  iack_queue ; 
 int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* tsi148_bridge ; 
 int /*<<< orphan*/  tsi148_iack_received () ; 
 int /*<<< orphan*/  vme_int ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tsi148_generate_irq(int level, int statid)
{
	u32 tmp;

	mutex_lock(&(vme_int));

	/* Read VICR register */
	tmp = ioread32be(tsi148_bridge->base + TSI148_LCSR_VICR);

	/* Set Status/ID */
	tmp = (tmp & ~TSI148_LCSR_VICR_STID_M) |
		(statid & TSI148_LCSR_VICR_STID_M);
	iowrite32be(tmp, tsi148_bridge->base + TSI148_LCSR_VICR);

	/* Assert VMEbus IRQ */
	tmp = tmp | TSI148_LCSR_VICR_IRQL[level];
	iowrite32be(tmp, tsi148_bridge->base + TSI148_LCSR_VICR);

	/* XXX Consider implementing a timeout? */
	wait_event_interruptible(iack_queue, tsi148_iack_received());

	mutex_unlock(&(vme_int));

	return 0;
}