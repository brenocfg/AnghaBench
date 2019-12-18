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
struct bpf_if {int (* bif_tap ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  bif_dlt; TYPE_1__* bif_ifp; struct bpf_if* bif_next; struct bpf_d* bif_dlist; } ;
struct bpf_d {int bd_flags; struct bpf_d* bd_next; struct bpf_if* bd_bif; } ;
typedef  int errno_t ;
struct TYPE_3__ {struct bpf_if* if_bpf; } ;

/* Variables and functions */
 int BPF_DETACHED ; 
 int BPF_DETACHING ; 
 int BPF_FINALIZE_PKTAP ; 
 int /*<<< orphan*/  BPF_TAP_INPUT_OUTPUT ; 
 int /*<<< orphan*/  DLT_PKTAP ; 
 int /*<<< orphan*/  bpf_acquire_d (struct bpf_d*) ; 
 struct bpf_if* bpf_iflist ; 
 int /*<<< orphan*/  bpf_tap_callback ; 
 int /*<<< orphan*/  dlil_set_bpf_tap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
bpf_attachd(struct bpf_d *d, struct bpf_if *bp)
{
	int first = bp->bif_dlist == NULL;
	int	error = 0;

	/*
	 * Point d at bp, and add d to the interface's list of listeners.
	 * Finally, point the driver's bpf cookie at the interface so
	 * it will divert packets to bpf.
	 */
	d->bd_bif = bp;
	d->bd_next = bp->bif_dlist;
	bp->bif_dlist = d;

	/*
	 * Take a reference on the device even if an error is returned
	 * because we keep the device in the interface's list of listeners
	 */
	bpf_acquire_d(d);

	if (first) {
		/* Find the default bpf entry for this ifp */
		if (bp->bif_ifp->if_bpf == NULL) {
			struct bpf_if	*tmp, *primary = NULL;

			for (tmp = bpf_iflist; tmp; tmp = tmp->bif_next) {
				if (tmp->bif_ifp == bp->bif_ifp) {
					primary = tmp;
					break;
				}
			}
			bp->bif_ifp->if_bpf = primary;
		}
		/* Only call dlil_set_bpf_tap for primary dlt */
		if (bp->bif_ifp->if_bpf == bp)
			dlil_set_bpf_tap(bp->bif_ifp, BPF_TAP_INPUT_OUTPUT,
			    bpf_tap_callback);

		if (bp->bif_tap != NULL)
			error = bp->bif_tap(bp->bif_ifp, bp->bif_dlt,
			    BPF_TAP_INPUT_OUTPUT);
	}

	/*
	 * Reset the detach flags in case we previously detached an interface
	 */
	d->bd_flags &= ~(BPF_DETACHING | BPF_DETACHED);

	if (bp->bif_dlt == DLT_PKTAP) {
		d->bd_flags |= BPF_FINALIZE_PKTAP;
	} else {
		d->bd_flags &= ~BPF_FINALIZE_PKTAP;
	}
	return (error);
}