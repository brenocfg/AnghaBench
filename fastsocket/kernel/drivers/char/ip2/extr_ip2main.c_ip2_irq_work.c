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
struct TYPE_6__ {int /*<<< orphan*/  tqueue_interrupt; int /*<<< orphan*/  i2eStartMail; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_MAIL_HERE ; 
 int /*<<< orphan*/  i2ServiceBoard (TYPE_1__*) ; 
 int /*<<< orphan*/  iiDisableMailIrq (TYPE_1__*) ; 
 int /*<<< orphan*/  iiGetMail (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ip2_irq_work(i2eBordStrPtr pB)
{
#ifdef USE_IQI
	if (NO_MAIL_HERE != ( pB->i2eStartMail = iiGetMail(pB))) {
//		Disable his interrupt (will be enabled when serviced)
//		This is mostly to protect from reentrancy.
		iiDisableMailIrq(pB);

//		Park the board on the immediate queue for processing.
		schedule_work(&pB->tqueue_interrupt);

//		Make sure the immediate queue is flagged to fire.
	}
#else

//	We are using immediate servicing here.  This sucks and can
//	cause all sorts of havoc with ppp and others.  The failsafe
//	check on iiSendPendingMail could also throw a hairball.

	i2ServiceBoard( pB );

#endif /* USE_IQI */
}