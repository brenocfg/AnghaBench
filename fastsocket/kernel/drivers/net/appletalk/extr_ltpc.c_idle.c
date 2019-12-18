#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xmitQel {int* cbuf; int cbuflen; int mailbox; int* dbuf; int dbuflen; int /*<<< orphan*/  QWrite; } ;
struct net_device {int base_addr; scalar_t__ irq; } ;
struct TYPE_3__ {int cbuflen; int dbuflen; int /*<<< orphan*/  mailbox; int /*<<< orphan*/  QWrite; void* dbuf; void* cbuf; } ;

/* Variables and functions */
 int DEBUG_LOWER ; 
 int QInIdle ; 
 struct xmitQel* deQ () ; 
 int debug ; 
 int /*<<< orphan*/  enQ (TYPE_1__*) ; 
 int /*<<< orphan*/  handlecommand (struct net_device*) ; 
 int /*<<< orphan*/  handlefc (struct net_device*) ; 
 int /*<<< orphan*/  handlefd (struct net_device*) ; 
 int /*<<< orphan*/  handleread (struct net_device*) ; 
 int /*<<< orphan*/  handlewrite (struct net_device*) ; 
 int inb_p (int) ; 
 int* ltdmabuf ; 
 int* ltdmacbuf ; 
 int* mailbox ; 
 int* mboxinuse ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__* qels ; 
 void* rescbuf ; 
 void* resdbuf ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  txqueue_lock ; 
 int /*<<< orphan*/  wait_timeout (struct net_device*,int) ; 
 int /*<<< orphan*/  xmQhd ; 

__attribute__((used)) static void idle(struct net_device *dev)
{
	unsigned long flags;
	int state;
	/* FIXME This is initialized to shut the warning up, but I need to
	 * think this through again.
	 */
	struct xmitQel *q = NULL;
	int oops;
	int i;
	int base = dev->base_addr;

	spin_lock_irqsave(&txqueue_lock, flags);
	if(QInIdle) {
		spin_unlock_irqrestore(&txqueue_lock, flags);
		return;
	}
	QInIdle = 1;
	spin_unlock_irqrestore(&txqueue_lock, flags);

	/* this tri-states the IRQ line */
	(void) inb_p(base+6);

	oops = 100;

loop:
	if (0>oops--) { 
		printk("idle: looped too many times\n");
		goto done;
	}

	state = inb_p(base+6);
	if (state != inb_p(base+6)) goto loop;

	switch(state) {
		case 0xfc:
			/* incoming command */
			if (debug & DEBUG_LOWER) printk("idle: fc\n");
			handlefc(dev); 
			break;
		case 0xfd:
			/* incoming data */
			if(debug & DEBUG_LOWER) printk("idle: fd\n");
			handlefd(dev); 
			break;
		case 0xf9:
			/* result ready */
			if (debug & DEBUG_LOWER) printk("idle: f9\n");
			if(!mboxinuse[0]) {
				mboxinuse[0] = 1;
				qels[0].cbuf = rescbuf;
				qels[0].cbuflen = 2;
				qels[0].dbuf = resdbuf;
				qels[0].dbuflen = 2;
				qels[0].QWrite = 0;
				qels[0].mailbox = 0;
				enQ(&qels[0]);
			}
			inb_p(dev->base_addr+1);
			inb_p(dev->base_addr+0);
			if( wait_timeout(dev,0xf9) )
				printk("timed out idle f9\n");
			break;
		case 0xf8:
			/* ?? */
			if (xmQhd) {
				inb_p(dev->base_addr+1);
				inb_p(dev->base_addr+0);
				if(wait_timeout(dev,0xf8) )
					printk("timed out idle f8\n");
			} else {
				goto done;
			}
			break;
		case 0xfa:
			/* waiting for command */
			if(debug & DEBUG_LOWER) printk("idle: fa\n");
			if (xmQhd) {
				q=deQ();
				memcpy(ltdmacbuf,q->cbuf,q->cbuflen);
				ltdmacbuf[1] = q->mailbox;
				if (debug>1) { 
					int n;
					printk("ltpc: sent command     ");
					n = q->cbuflen;
					if (n>100) n=100;
					for(i=0;i<n;i++)
						printk("%02x ",ltdmacbuf[i]);
					printk("\n");
				}
				handlecommand(dev);
					if(0xfa==inb_p(base+6)) {
						/* we timed out, so return */
						goto done;
					} 
			} else {
				/* we don't seem to have a command */
				if (!mboxinuse[0]) {
					mboxinuse[0] = 1;
					qels[0].cbuf = rescbuf;
					qels[0].cbuflen = 2;
					qels[0].dbuf = resdbuf;
					qels[0].dbuflen = 2;
					qels[0].QWrite = 0;
					qels[0].mailbox = 0;
					enQ(&qels[0]);
				} else {
					printk("trouble: response command already queued\n");
					goto done;
				}
			} 
			break;
		case 0Xfb:
			/* data transfer ready */
			if(debug & DEBUG_LOWER) printk("idle: fb\n");
			if(q->QWrite) {
				memcpy(ltdmabuf,q->dbuf,q->dbuflen);
				handlewrite(dev);
			} else {
				handleread(dev);
				/* non-zero mailbox numbers are for
				   commmands, 0 is for GETRESULT
				   requests */
				if(q->mailbox) {
					memcpy(q->dbuf,ltdmabuf,q->dbuflen);
				} else { 
					/* this was a result */
					mailbox[ 0x0f & ltdmabuf[0] ] = ltdmabuf[1];
					mboxinuse[0]=0;
				}
			}
			break;
	}
	goto loop;

done:
	QInIdle=0;

	/* now set the interrupts back as appropriate */
	/* the first read takes it out of tri-state (but still high) */
	/* the second resets it */
	/* note that after this point, any read of base+6 will
	   trigger an interrupt */

	if (dev->irq) {
		inb_p(base+7);
		inb_p(base+7);
	}
	return;
}