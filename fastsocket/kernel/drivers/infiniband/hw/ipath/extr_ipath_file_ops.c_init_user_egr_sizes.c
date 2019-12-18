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
struct ipath_portdata {unsigned int port_rcvegrbuf_chunks; unsigned int port_rcvegrbufs_perchunk; unsigned int port_rcvegrbuf_size; struct ipath_devdata* port_dd; } ;
struct ipath_devdata {unsigned int ipath_rcvegrbufsize; unsigned int ipath_rcvegrcnt; } ;

/* Variables and functions */

__attribute__((used)) static void init_user_egr_sizes(struct ipath_portdata *pd)
{
	struct ipath_devdata *dd = pd->port_dd;
	unsigned egrperchunk, egrcnt, size;

	/*
	 * to avoid wasting a lot of memory, we allocate 32KB chunks of
	 * physically contiguous memory, advance through it until used up
	 * and then allocate more.  Of course, we need memory to store those
	 * extra pointers, now.  Started out with 256KB, but under heavy
	 * memory pressure (creating large files and then copying them over
	 * NFS while doing lots of MPI jobs), we hit some allocation
	 * failures, even though we can sleep...  (2.6.10) Still get
	 * failures at 64K.  32K is the lowest we can go without wasting
	 * additional memory.
	 */
	size = 0x8000;
	egrperchunk = size / dd->ipath_rcvegrbufsize;
	egrcnt = dd->ipath_rcvegrcnt;
	pd->port_rcvegrbuf_chunks = (egrcnt + egrperchunk - 1) / egrperchunk;
	pd->port_rcvegrbufs_perchunk = egrperchunk;
	pd->port_rcvegrbuf_size = size;
}