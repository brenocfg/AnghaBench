#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qib_ctxtdata {int /*<<< orphan*/ * user_event_mask; } ;

/* Variables and functions */
 int _QIB_EVENT_DISARM_BUFS_BIT ; 
 int _QIB_MAX_EVENT_BIT ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int disarm_req_delay (struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  qib_disarm_piobufs_ifneeded (struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

__attribute__((used)) static int qib_user_event_ack(struct qib_ctxtdata *rcd, int subctxt,
			      unsigned long events)
{
	int ret = 0, i;

	for (i = 0; i <= _QIB_MAX_EVENT_BIT; i++) {
		if (!test_bit(i, &events))
			continue;
		if (i == _QIB_EVENT_DISARM_BUFS_BIT) {
			(void)qib_disarm_piobufs_ifneeded(rcd);
			ret = disarm_req_delay(rcd);
		} else
			clear_bit(i, &rcd->user_event_mask[subctxt]);
	}
	return ret;
}