#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int head; int tail; void** buf; } ;
struct iforce {int bus; int /*<<< orphan*/  xmit_flags; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  xmit_lock; TYPE_2__ xmit; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CIRC_SPACE (int,int,int /*<<< orphan*/ ) ; 
 int CIRC_SPACE_TO_END (int,int,int /*<<< orphan*/ ) ; 
 void* HI (int /*<<< orphan*/ ) ; 
#define  IFORCE_232 129 
#define  IFORCE_USB 128 
 int /*<<< orphan*/  IFORCE_XMIT_RUNNING ; 
 void* LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMIT_INC (int,int) ; 
 int /*<<< orphan*/  XMIT_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iforce_serial_xmit (struct iforce*) ; 
 int /*<<< orphan*/  iforce_usb_xmit (struct iforce*) ; 
 int /*<<< orphan*/  memcpy (void**,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iforce_send_packet(struct iforce *iforce, u16 cmd, unsigned char* data)
{
	/* Copy data to buffer */
	int n = LO(cmd);
	int c;
	int empty;
	int head, tail;
	unsigned long flags;

/*
 * Update head and tail of xmit buffer
 */
	spin_lock_irqsave(&iforce->xmit_lock, flags);

	head = iforce->xmit.head;
	tail = iforce->xmit.tail;


	if (CIRC_SPACE(head, tail, XMIT_SIZE) < n+2) {
		dev_warn(&iforce->dev->dev,
			 "not enough space in xmit buffer to send new packet\n");
		spin_unlock_irqrestore(&iforce->xmit_lock, flags);
		return -1;
	}

	empty = head == tail;
	XMIT_INC(iforce->xmit.head, n+2);

/*
 * Store packet in xmit buffer
 */
	iforce->xmit.buf[head] = HI(cmd);
	XMIT_INC(head, 1);
	iforce->xmit.buf[head] = LO(cmd);
	XMIT_INC(head, 1);

	c = CIRC_SPACE_TO_END(head, tail, XMIT_SIZE);
	if (n < c) c=n;

	memcpy(&iforce->xmit.buf[head],
	       data,
	       c);
	if (n != c) {
		memcpy(&iforce->xmit.buf[0],
		       data + c,
		       n - c);
	}
	XMIT_INC(head, n);

	spin_unlock_irqrestore(&iforce->xmit_lock, flags);
/*
 * If necessary, start the transmission
 */
	switch (iforce->bus) {

#ifdef CONFIG_JOYSTICK_IFORCE_232
		case IFORCE_232:
		if (empty)
			iforce_serial_xmit(iforce);
		break;
#endif
#ifdef CONFIG_JOYSTICK_IFORCE_USB
		case IFORCE_USB:

		if (iforce->usbdev && empty &&
			!test_and_set_bit(IFORCE_XMIT_RUNNING, iforce->xmit_flags)) {

			iforce_usb_xmit(iforce);
		}
		break;
#endif
	}
	return 0;
}