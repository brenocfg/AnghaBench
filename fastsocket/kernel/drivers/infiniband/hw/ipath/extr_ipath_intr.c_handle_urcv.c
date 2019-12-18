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
typedef  int u64 ;
struct ipath_portdata {int /*<<< orphan*/  port_wait; int /*<<< orphan*/  port_urgent; int /*<<< orphan*/  port_flag; scalar_t__ port_cnt; } ;
struct ipath_devdata {int ipath_i_rcvavail_shift; int ipath_i_rcvavail_mask; int ipath_i_rcvurg_shift; int ipath_i_rcvurg_mask; int ipath_cfgports; int /*<<< orphan*/  ipath_rcvctrl; TYPE_1__* ipath_kregs; scalar_t__ ipath_r_intravail_shift; struct ipath_portdata** ipath_pd; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_rcvctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPATH_PORT_WAITING_RCV ; 
 int /*<<< orphan*/  IPATH_PORT_WAITING_URG ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_urcv(struct ipath_devdata *dd, u64 istat)
{
	u64 portr;
	int i;
	int rcvdint = 0;

	/*
	 * test_and_clear_bit(IPATH_PORT_WAITING_RCV) and
	 * test_and_clear_bit(IPATH_PORT_WAITING_URG) below
	 * would both like timely updates of the bits so that
	 * we don't pass them by unnecessarily.  the rmb()
	 * here ensures that we see them promptly -- the
	 * corresponding wmb()'s are in ipath_poll_urgent()
	 * and ipath_poll_next()...
	 */
	rmb();
	portr = ((istat >> dd->ipath_i_rcvavail_shift) &
		 dd->ipath_i_rcvavail_mask) |
		((istat >> dd->ipath_i_rcvurg_shift) &
		 dd->ipath_i_rcvurg_mask);
	for (i = 1; i < dd->ipath_cfgports; i++) {
		struct ipath_portdata *pd = dd->ipath_pd[i];

		if (portr & (1 << i) && pd && pd->port_cnt) {
			if (test_and_clear_bit(IPATH_PORT_WAITING_RCV,
					       &pd->port_flag)) {
				clear_bit(i + dd->ipath_r_intravail_shift,
					  &dd->ipath_rcvctrl);
				wake_up_interruptible(&pd->port_wait);
				rcvdint = 1;
			} else if (test_and_clear_bit(IPATH_PORT_WAITING_URG,
						      &pd->port_flag)) {
				pd->port_urgent++;
				wake_up_interruptible(&pd->port_wait);
			}
		}
	}
	if (rcvdint) {
		/* only want to take one interrupt, so turn off the rcv
		 * interrupt for all the ports that we set the rcv_waiting
		 * (but never for kernel port)
		 */
		ipath_write_kreg(dd, dd->ipath_kregs->kr_rcvctrl,
				 dd->ipath_rcvctrl);
	}
}