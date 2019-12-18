#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2eBordStrPtr ;
struct TYPE_5__ {scalar_t__ i2eValid; scalar_t__ i2eFatal; int /*<<< orphan*/ * i2eFatalTrap; scalar_t__ i2eFifoOutInts; scalar_t__ i2eFifoInInts; scalar_t__* i2eLeadoffWord; scalar_t__ i2eChannelCnt; int /*<<< orphan*/ * i2eChannelPtr; scalar_t__ i2eOutMailWaiting; scalar_t__ i2eWaitingForEmptyFifo; int /*<<< orphan*/  i2eUsingIrq; int /*<<< orphan*/  i2eState; scalar_t__ i2eBase; } ;

/* Variables and functions */
 scalar_t__ FIFO_RESET ; 
 int /*<<< orphan*/  I2EE_BADMAGIC ; 
 int /*<<< orphan*/  I2EE_GOOD ; 
 scalar_t__ I2E_MAGIC ; 
 int /*<<< orphan*/  I2_COMPLETE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2_IRQ_UNDEFINED ; 
 int /*<<< orphan*/  II_STATE_RESET ; 
 int /*<<< orphan*/  iiDelay (TYPE_1__*,int) ; 
 scalar_t__ iiDelayed ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
iiReset(i2eBordStrPtr pB)
{
	// Magic number should be set, else even the address is suspect
	if (pB->i2eValid != I2E_MAGIC)
	{
		I2_COMPLETE(pB, I2EE_BADMAGIC);
	}

	outb(0, pB->i2eBase + FIFO_RESET);  /* Any data will do */
	iiDelay(pB, 50);                    // Pause between resets
	outb(0, pB->i2eBase + FIFO_RESET);  /* Second reset */

	// We must wait before even attempting to read anything from the FIFO: the
	// board's P.O.S.T may actually attempt to read and write its end of the
	// FIFO in order to check flags, loop back (where supported), etc. On
	// completion of this testing it would reset the FIFO, and on completion
	// of all // P.O.S.T., write the message. We must not mistake data which
	// might have been sent for testing as part of the reset message. To
	// better utilize time, say, when resetting several boards, we allow the
	// delay to be performed externally; in this way the caller can reset 
	// several boards, delay a single time, then call the initialization
	// routine for all.

	pB->i2eState = II_STATE_RESET;

	iiDelayed = 0;	// i.e., the delay routine hasn't been called since the most
					// recent reset.

	// Ensure anything which would have been of use to standard loadware is
	// blanked out, since board has now forgotten everything!.

	pB->i2eUsingIrq = I2_IRQ_UNDEFINED; /* to not use an interrupt so far */
	pB->i2eWaitingForEmptyFifo = 0;
	pB->i2eOutMailWaiting = 0;
	pB->i2eChannelPtr = NULL;
	pB->i2eChannelCnt = 0;

	pB->i2eLeadoffWord[0] = 0;
	pB->i2eFifoInInts = 0;
	pB->i2eFifoOutInts = 0;
	pB->i2eFatalTrap = NULL;
	pB->i2eFatal = 0;

	I2_COMPLETE(pB, I2EE_GOOD);
}