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
struct poll_table_struct {int dummy; } ;
struct ipath_portdata {int /*<<< orphan*/  port_wait; scalar_t__ port_port; int /*<<< orphan*/  port_flag; scalar_t__ port_rcvhdrtail_kvaddr; struct ipath_devdata* port_dd; } ;
struct ipath_devdata {int ipath_rhdrhead_intr_off; int /*<<< orphan*/  ipath_rcvctrl; TYPE_1__* ipath_kregs; scalar_t__ ipath_r_intravail_shift; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_rcvctrl; } ;

/* Variables and functions */
 scalar_t__ IPATH_PORT_WAITING_RCV ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int ipath_get_rcvhdrtail (struct ipath_portdata*) ; 
 unsigned int ipath_poll_hdrqfull (struct ipath_portdata*) ; 
 int ipath_read_ureg32 (struct ipath_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_ureg (struct ipath_devdata*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ur_rcvhdrhead ; 
 int /*<<< orphan*/  ur_rcvhdrtail ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static unsigned int ipath_poll_next(struct ipath_portdata *pd,
				    struct file *fp,
				    struct poll_table_struct *pt)
{
	u32 head;
	u32 tail;
	unsigned pollflag = 0;
	struct ipath_devdata *dd;

	dd = pd->port_dd;

	/* variable access in ipath_poll_hdrqfull() needs this */
	rmb();
	pollflag = ipath_poll_hdrqfull(pd);

	head = ipath_read_ureg32(dd, ur_rcvhdrhead, pd->port_port);
	if (pd->port_rcvhdrtail_kvaddr)
		tail = ipath_get_rcvhdrtail(pd);
	else
		tail = ipath_read_ureg32(dd, ur_rcvhdrtail, pd->port_port);

	if (head != tail)
		pollflag |= POLLIN | POLLRDNORM;
	else {
		/* this saves a spin_lock/unlock in interrupt handler */
		set_bit(IPATH_PORT_WAITING_RCV, &pd->port_flag);
		/* flush waiting flag so we don't miss an event */
		wmb();

		set_bit(pd->port_port + dd->ipath_r_intravail_shift,
			&dd->ipath_rcvctrl);

		ipath_write_kreg(dd, dd->ipath_kregs->kr_rcvctrl,
				 dd->ipath_rcvctrl);

		if (dd->ipath_rhdrhead_intr_off) /* arm rcv interrupt */
			ipath_write_ureg(dd, ur_rcvhdrhead,
					 dd->ipath_rhdrhead_intr_off | head,
					 pd->port_port);

		poll_wait(fp, &pd->port_wait, pt);
	}

	return pollflag;
}