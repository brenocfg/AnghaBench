#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * le_prev; int /*<<< orphan*/ * le_next; } ;
struct TYPE_4__ {int /*<<< orphan*/ * le_prev; int /*<<< orphan*/ * le_next; } ;
struct inpcbport {int inp_flags2; scalar_t__ inp_lport; TYPE_3__* inp_pcbinfo; int /*<<< orphan*/  inp_flowhash; struct inpcbport* inp_phd; int /*<<< orphan*/  phd_pcblist; TYPE_2__ inp_portlist; TYPE_1__ inp_hash; scalar_t__ inp_gencnt; } ;
struct inpcb {int inp_flags2; scalar_t__ inp_lport; TYPE_3__* inp_pcbinfo; int /*<<< orphan*/  inp_flowhash; struct inpcb* inp_phd; int /*<<< orphan*/  phd_pcblist; TYPE_2__ inp_portlist; TYPE_1__ inp_hash; scalar_t__ inp_gencnt; } ;
struct TYPE_6__ {scalar_t__ ipi_twcount; int /*<<< orphan*/  ipi_count; scalar_t__ ipi_gencnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct inpcbport*,int /*<<< orphan*/ ) ; 
 int INP2_INHASHLIST ; 
 int INP2_IN_FCTREE ; 
 int INP2_TIMEWAIT ; 
 int INPFC_REMOVE ; 
 int INPFC_SOLOCKED ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct inpcbport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PCB ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  inp_fc_getinp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inp_hash ; 
 int /*<<< orphan*/  inp_list ; 
 int /*<<< orphan*/  inp_portlist ; 
 int /*<<< orphan*/  phd_hash ; 
 int /*<<< orphan*/  tcp_remove_from_time_wait (struct inpcbport*) ; 

void
in_pcbremlists(struct inpcb *inp)
{
	inp->inp_gencnt = ++inp->inp_pcbinfo->ipi_gencnt;

	/*
	 * Check if it's in hashlist -- an inp is placed in hashlist when
	 * it's local port gets assigned. So it should also be present
	 * in the port list.
	 */
	if (inp->inp_flags2 & INP2_INHASHLIST) {
		struct inpcbport *phd = inp->inp_phd;

		VERIFY(phd != NULL && inp->inp_lport > 0);

		LIST_REMOVE(inp, inp_hash);
		inp->inp_hash.le_next = NULL;
		inp->inp_hash.le_prev = NULL;

		LIST_REMOVE(inp, inp_portlist);
		inp->inp_portlist.le_next = NULL;
		inp->inp_portlist.le_prev = NULL;
		if (LIST_EMPTY(&phd->phd_pcblist)) {
			LIST_REMOVE(phd, phd_hash);
			FREE(phd, M_PCB);
		}
		inp->inp_phd = NULL;
		inp->inp_flags2 &= ~INP2_INHASHLIST;
	}
	VERIFY(!(inp->inp_flags2 & INP2_INHASHLIST));

	if (inp->inp_flags2 & INP2_TIMEWAIT) {
		/* Remove from time-wait queue */
		tcp_remove_from_time_wait(inp);
		inp->inp_flags2 &= ~INP2_TIMEWAIT;
		VERIFY(inp->inp_pcbinfo->ipi_twcount != 0);
		inp->inp_pcbinfo->ipi_twcount--;
	} else {
		/* Remove from global inp list if it is not time-wait */
		LIST_REMOVE(inp, inp_list);
	}

	if (inp->inp_flags2 & INP2_IN_FCTREE) {
		inp_fc_getinp(inp->inp_flowhash, (INPFC_SOLOCKED|INPFC_REMOVE));
		VERIFY(!(inp->inp_flags2 & INP2_IN_FCTREE));
	}

	inp->inp_pcbinfo->ipi_count--;
}