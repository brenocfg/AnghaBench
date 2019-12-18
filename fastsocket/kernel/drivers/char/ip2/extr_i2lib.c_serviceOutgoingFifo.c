#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2eBordStrPtr ;
struct TYPE_7__ {int /*<<< orphan*/  i2eWaitingForEmptyFifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2StuffFifoBypass (TYPE_1__*) ; 
 int /*<<< orphan*/  i2StuffFifoFlow (TYPE_1__*) ; 
 int /*<<< orphan*/  i2StuffFifoInline (TYPE_1__*) ; 
 int /*<<< orphan*/  iiSendPendingMail (TYPE_1__*) ; 

__attribute__((used)) static void
serviceOutgoingFifo(i2eBordStrPtr pB)
{
	// If we aren't currently waiting for the board to empty our fifo, service
	// everything that is pending, in priority order (especially, Bypass before
	// Inline).
	if ( ! pB->i2eWaitingForEmptyFifo )
	{
		i2StuffFifoFlow(pB);
		i2StuffFifoBypass(pB);
		i2StuffFifoInline(pB);

		iiSendPendingMail(pB);
	} 
}