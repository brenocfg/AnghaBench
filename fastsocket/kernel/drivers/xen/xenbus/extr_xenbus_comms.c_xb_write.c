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
struct xenstore_domain_interface {scalar_t__ req_prod; scalar_t__ req_cons; int /*<<< orphan*/  req; } ;
typedef  scalar_t__ XENSTORE_RING_IDX ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ XENSTORE_RING_SIZE ; 
 int /*<<< orphan*/  check_indexes (scalar_t__,scalar_t__) ; 
 void* get_output_chunk (scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xb_waitq ; 
 int /*<<< orphan*/  xen_store_evtchn ; 
 struct xenstore_domain_interface* xen_store_interface ; 

int xb_write(const void *data, unsigned len)
{
	struct xenstore_domain_interface *intf = xen_store_interface;
	XENSTORE_RING_IDX cons, prod;
	int rc;

	while (len != 0) {
		void *dst;
		unsigned int avail;

		rc = wait_event_interruptible(
			xb_waitq,
			(intf->req_prod - intf->req_cons) !=
			XENSTORE_RING_SIZE);
		if (rc < 0)
			return rc;

		/* Read indexes, then verify. */
		cons = intf->req_cons;
		prod = intf->req_prod;
		if (!check_indexes(cons, prod)) {
			intf->req_cons = intf->req_prod = 0;
			return -EIO;
		}

		dst = get_output_chunk(cons, prod, intf->req, &avail);
		if (avail == 0)
			continue;
		if (avail > len)
			avail = len;

		/* Must write data /after/ reading the consumer index. */
		mb();

		memcpy(dst, data, avail);
		data += avail;
		len -= avail;

		/* Other side must not see new producer until data is there. */
		wmb();
		intf->req_prod += avail;

		/* Implies mb(): other side will see the updated producer. */
		notify_remote_via_evtchn(xen_store_evtchn);
	}

	return 0;
}