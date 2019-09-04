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
struct ifnet {int dummy; } ;
struct bpf_if {scalar_t__ bif_dlt; struct ifnet* bif_ifp; struct bpf_if* bif_next; } ;
struct bpf_d {scalar_t__ bd_hbuf_read; int bd_flags; struct bpf_if* bd_bif; } ;
typedef  struct ifnet* ifnet_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int BPF_CLOSING ; 
 int BPF_WANT_PKTAP ; 
 scalar_t__ DLT_PKTAP ; 
 int ENXIO ; 
 scalar_t__ IFNET_IS_INTCOPROC (struct ifnet*) ; 
 int /*<<< orphan*/  PRINET ; 
 int bpf_allocbufs (struct bpf_d*) ; 
 scalar_t__ bpf_attachd (struct bpf_d*,struct bpf_if*) ; 
 scalar_t__ bpf_detachd (struct bpf_d*,int /*<<< orphan*/ ) ; 
 struct bpf_if* bpf_iflist ; 
 int /*<<< orphan*/  bpf_mlock ; 
 int /*<<< orphan*/  intcoproc_unrestricted ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_d (struct bpf_d*) ; 

__attribute__((used)) static int
bpf_setif(struct bpf_d *d, ifnet_t theywant, bool do_reset, bool has_hbuf_read)
{
	struct bpf_if *bp;
	int error;

	while (d->bd_hbuf_read != 0 && !has_hbuf_read)
		msleep((caddr_t)d, bpf_mlock, PRINET, "bpf_reading", NULL);

	if ((d->bd_flags & BPF_CLOSING) != 0)
		return (ENXIO);

	/*
	 * Look through attached interfaces for the named one.
	 */
	for (bp = bpf_iflist; bp != 0; bp = bp->bif_next) {
		struct ifnet *ifp = bp->bif_ifp;

		if (ifp == 0 || ifp != theywant)
			continue;
		/*
		 * Do not use DLT_PKTAP, unless requested explicitly
		 */
		if (bp->bif_dlt == DLT_PKTAP && !(d->bd_flags & BPF_WANT_PKTAP))
			continue;
		/*
		 * Skip the coprocessor interface
		 */
		if (!intcoproc_unrestricted && IFNET_IS_INTCOPROC(ifp))
			continue;
		/*
		 * We found the requested interface.
		 * Allocate the packet buffers.
		 */
		error = bpf_allocbufs(d);
		if (error != 0)
			return (error);
		/*
		 * Detach if attached to something else.
		 */
		if (bp != d->bd_bif) {
			if (d->bd_bif != NULL) {
				if (bpf_detachd(d, 0) != 0)
					return (ENXIO);
			}
			if (bpf_attachd(d, bp) != 0)
				return (ENXIO);
		}
		if (do_reset) {
		reset_d(d);
		}
		return (0);
	}
	/* Not found. */
	return (ENXIO);
}