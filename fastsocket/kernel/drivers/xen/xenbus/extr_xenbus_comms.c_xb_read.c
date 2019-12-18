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
struct xenstore_domain_interface {scalar_t__ rsp_cons; int /*<<< orphan*/  rsp; scalar_t__ rsp_prod; } ;
typedef  scalar_t__ XENSTORE_RING_IDX ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  check_indexes (scalar_t__,scalar_t__) ; 
 char* get_input_chunk (scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (void*,char const*,unsigned int) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rmb () ; 
 int xb_wait_for_data_to_read () ; 
 int /*<<< orphan*/  xen_store_evtchn ; 
 struct xenstore_domain_interface* xen_store_interface ; 

int xb_read(void *data, unsigned len)
{
	struct xenstore_domain_interface *intf = xen_store_interface;
	XENSTORE_RING_IDX cons, prod;
	int rc;

	while (len != 0) {
		unsigned int avail;
		const char *src;

		rc = xb_wait_for_data_to_read();
		if (rc < 0)
			return rc;

		/* Read indexes, then verify. */
		cons = intf->rsp_cons;
		prod = intf->rsp_prod;
		if (!check_indexes(cons, prod)) {
			intf->rsp_cons = intf->rsp_prod = 0;
			return -EIO;
		}

		src = get_input_chunk(cons, prod, intf->rsp, &avail);
		if (avail == 0)
			continue;
		if (avail > len)
			avail = len;

		/* Must read data /after/ reading the producer index. */
		rmb();

		memcpy(data, src, avail);
		data += avail;
		len -= avail;

		/* Other side must not see free space until we've copied out */
		mb();
		intf->rsp_cons += avail;

		pr_debug("Finished read of %i bytes (%i to go)\n", avail, len);

		/* Implies mb(): other side will see the updated consumer. */
		notify_remote_via_evtchn(xen_store_evtchn);
	}

	return 0;
}