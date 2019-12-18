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
struct TYPE_6__ {unsigned int i2eStartMail; int i2eFatal; int /*<<< orphan*/  i2eFifoRemains; int /*<<< orphan*/  write_fifo_spinlock; scalar_t__ i2eWaitingForEmptyFifo; int /*<<< orphan*/  i2eFifoSize; int /*<<< orphan*/  i2eFifoOutInts; int /*<<< orphan*/  i2eFifoInInts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITRC_INTR ; 
 int /*<<< orphan*/  ITRC_NO_PORT ; 
 unsigned int MB_FATAL_ERROR ; 
 unsigned int MB_IN_STUFFED ; 
 unsigned int MB_OUT_STRIPPED ; 
 unsigned int NO_MAIL_HERE ; 
 int /*<<< orphan*/  i2StripFifo (TYPE_1__*) ; 
 unsigned int iiGetMail (TYPE_1__*) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  serviceOutgoingFifo (TYPE_1__*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int
i2ServiceBoard ( i2eBordStrPtr pB )
{
	unsigned inmail;
	unsigned long flags;


	/* This should be atomic because of the way we are called... */
	if (NO_MAIL_HERE == ( inmail = pB->i2eStartMail ) ) {
		inmail = iiGetMail(pB);
	}
	pB->i2eStartMail = NO_MAIL_HERE;

	ip2trace (ITRC_NO_PORT, ITRC_INTR, 2, 1, inmail );

	if (inmail != NO_MAIL_HERE) {
		// If the board has gone fatal, nothing to do but hit a bit that will
		// alert foreground tasks to protest!
		if ( inmail & MB_FATAL_ERROR ) {
			pB->i2eFatal = 1;
			goto exit_i2ServiceBoard;
		}

		/* Assuming no fatal condition, we proceed to do work */
		if ( inmail & MB_IN_STUFFED ) {
			pB->i2eFifoInInts++;
			i2StripFifo(pB);     /* There might be incoming packets */
		}

		if (inmail & MB_OUT_STRIPPED) {
			pB->i2eFifoOutInts++;
			write_lock_irqsave(&pB->write_fifo_spinlock, flags);
			pB->i2eFifoRemains = pB->i2eFifoSize;
			pB->i2eWaitingForEmptyFifo = 0;
			write_unlock_irqrestore(&pB->write_fifo_spinlock,
					flags);

			ip2trace (ITRC_NO_PORT, ITRC_INTR, 30, 1, pB->i2eFifoRemains );

		}
		serviceOutgoingFifo(pB);
	}

	ip2trace (ITRC_NO_PORT, ITRC_INTR, 8, 0 );

exit_i2ServiceBoard:

	return 0;
}