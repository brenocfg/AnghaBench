#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2eBordStrPtr ;
struct TYPE_6__ {int /*<<< orphan*/  i2eStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  Dl_spinlock ; 
 int /*<<< orphan*/  I2EE_GOOD ; 
 int /*<<< orphan*/  I2EE_TXE_TIME ; 
 int /*<<< orphan*/  I2_COMPLETE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2_UPDATE_FIFO_ROOM (TYPE_1__*) ; 
 int STE_OUT_MT ; 
 int /*<<< orphan*/  iiDelay (TYPE_1__*,int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
iiWaitForTxEmptyIIEX(i2eBordStrPtr pB, int mSdelay)
{
	unsigned long	flags;

	for (;;)
	{
		// By the nature of this routine, you would be using this as part of a
		// larger atomic context: i.e., you would use this routine to ensure the
		// fifo empty, then act on this information. Between these two halves,
		// you will generally not want to service interrupts or in any way
		// disrupt the assumptions implicit in the larger context.

		write_lock_irqsave(&Dl_spinlock, flags);

		if (inb(pB->i2eStatus) & STE_OUT_MT) {
			I2_UPDATE_FIFO_ROOM(pB);
			write_unlock_irqrestore(&Dl_spinlock, flags);
			I2_COMPLETE(pB, I2EE_GOOD);
		}
		write_unlock_irqrestore(&Dl_spinlock, flags);

		if (mSdelay-- == 0)
			break;

		iiDelay(pB, 1);      // 1 mS granularity on checking condition
	}
	I2_COMPLETE(pB, I2EE_TXE_TIME);
}