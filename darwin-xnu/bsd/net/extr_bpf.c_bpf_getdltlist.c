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
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ u_int ;
struct proc {int dummy; } ;
struct ifnet {int dummy; } ;
struct bpf_if {scalar_t__ bif_dlt; struct ifnet* bif_ifp; struct bpf_if* bif_next; } ;
struct TYPE_3__ {int /*<<< orphan*/  bflu_list; scalar_t__ bflu_pad; } ;
struct bpf_dltlist {scalar_t__ bfl_len; TYPE_1__ bfl_u; } ;
struct bpf_d {int bd_flags; TYPE_2__* bd_bif; } ;
typedef  struct bpf_dltlist* caddr_t ;
typedef  int /*<<< orphan*/  bfl ;
struct TYPE_4__ {struct ifnet* bif_ifp; } ;

/* Variables and functions */
 int BPF_WANT_PKTAP ; 
 scalar_t__ CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
 scalar_t__ DLT_PKTAP ; 
 int ENOMEM ; 
 scalar_t__ USER_ADDR_NULL ; 
 int /*<<< orphan*/  bcopy (struct bpf_dltlist*,struct bpf_dltlist*,int) ; 
 struct bpf_if* bpf_iflist ; 
 int copyout (scalar_t__*,scalar_t__,int) ; 
 scalar_t__ proc_is64bit (struct proc*) ; 

__attribute__((used)) static int
bpf_getdltlist(struct bpf_d *d, caddr_t addr, struct proc *p)
{
	u_int		n;
	int		error;
	struct ifnet	*ifp;
	struct bpf_if	*bp;
	user_addr_t	dlist;
	struct bpf_dltlist bfl;

	bcopy(addr, &bfl, sizeof (bfl));
	if (proc_is64bit(p)) {
		dlist = (user_addr_t)bfl.bfl_u.bflu_pad;
	} else {
		dlist = CAST_USER_ADDR_T(bfl.bfl_u.bflu_list);
	}

	ifp = d->bd_bif->bif_ifp;
	n = 0;
	error = 0;

	for (bp = bpf_iflist; bp; bp = bp->bif_next) {
		if (bp->bif_ifp != ifp)
			continue;
		/*
		 * Do not use DLT_PKTAP, unless requested explicitly
		 */
		if (bp->bif_dlt == DLT_PKTAP && !(d->bd_flags & BPF_WANT_PKTAP))
			continue;
		if (dlist != USER_ADDR_NULL) {
			if (n >= bfl.bfl_len) {
				return (ENOMEM);
			}
			error = copyout(&bp->bif_dlt, dlist,
			    sizeof (bp->bif_dlt));
			if (error != 0)
				break;
			dlist += sizeof (bp->bif_dlt);
		}
		n++;
	}
	bfl.bfl_len = n;
	bcopy(&bfl, addr, sizeof (bfl));

	return (error);
}