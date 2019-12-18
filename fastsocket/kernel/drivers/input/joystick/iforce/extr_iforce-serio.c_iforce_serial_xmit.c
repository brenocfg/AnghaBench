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
struct TYPE_2__ {size_t head; size_t tail; unsigned char* buf; } ;
struct iforce {int /*<<< orphan*/  xmit_lock; int /*<<< orphan*/  xmit_flags; int /*<<< orphan*/  serio; TYPE_1__ xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFORCE_XMIT_AGAIN ; 
 int /*<<< orphan*/  IFORCE_XMIT_RUNNING ; 
 int /*<<< orphan*/  XMIT_INC (size_t,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_write (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iforce_serial_xmit(struct iforce *iforce)
{
	unsigned char cs;
	int i;
	unsigned long flags;

	if (test_and_set_bit(IFORCE_XMIT_RUNNING, iforce->xmit_flags)) {
		set_bit(IFORCE_XMIT_AGAIN, iforce->xmit_flags);
		return;
	}

	spin_lock_irqsave(&iforce->xmit_lock, flags);

again:
	if (iforce->xmit.head == iforce->xmit.tail) {
		clear_bit(IFORCE_XMIT_RUNNING, iforce->xmit_flags);
		spin_unlock_irqrestore(&iforce->xmit_lock, flags);
		return;
	}

	cs = 0x2b;

	serio_write(iforce->serio, 0x2b);

	serio_write(iforce->serio, iforce->xmit.buf[iforce->xmit.tail]);
	cs ^= iforce->xmit.buf[iforce->xmit.tail];
	XMIT_INC(iforce->xmit.tail, 1);

	for (i=iforce->xmit.buf[iforce->xmit.tail]; i >= 0; --i) {
		serio_write(iforce->serio, iforce->xmit.buf[iforce->xmit.tail]);
		cs ^= iforce->xmit.buf[iforce->xmit.tail];
		XMIT_INC(iforce->xmit.tail, 1);
	}

	serio_write(iforce->serio, cs);

	if (test_and_clear_bit(IFORCE_XMIT_AGAIN, iforce->xmit_flags))
		goto again;

	clear_bit(IFORCE_XMIT_RUNNING, iforce->xmit_flags);

	spin_unlock_irqrestore(&iforce->xmit_lock, flags);
}