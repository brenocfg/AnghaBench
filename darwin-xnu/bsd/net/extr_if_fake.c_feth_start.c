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
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/  iff_flags_t ;
typedef  TYPE_1__* if_fake_ref ;
struct TYPE_3__ {struct mbuf* iff_pending_tx_packet; int /*<<< orphan*/ * iff_peer; scalar_t__ iff_start_busy; int /*<<< orphan*/  iff_flags; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct mbuf* copy_mbuf (struct mbuf*) ; 
 int /*<<< orphan*/  feth_lock () ; 
 int /*<<< orphan*/  feth_output_common (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feth_unlock () ; 
 scalar_t__ ifnet_dequeue (int /*<<< orphan*/ *,struct mbuf**) ; 
 TYPE_1__* ifnet_get_if_fake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
feth_start(ifnet_t ifp)
{
	struct mbuf *	copy_m = NULL;
	if_fake_ref	fakeif;
	iff_flags_t	flags = 0;
	ifnet_t	peer = NULL;
	struct mbuf *	m;
	struct mbuf *	save_m;

	feth_lock();
	fakeif = ifnet_get_if_fake(ifp);
	if (fakeif->iff_start_busy) {
		feth_unlock();
		printf("if_fake: start is busy\n");
		return;
	}
	if (fakeif != NULL) {
		peer = fakeif->iff_peer;
		flags = fakeif->iff_flags;
	}

	/* check for pending TX */
	m = fakeif->iff_pending_tx_packet;
	if (m != NULL) {
		if (peer != NULL) {
			copy_m = copy_mbuf(m);
			if (copy_m == NULL) {
				feth_unlock();
				return;
			}
		}
		fakeif->iff_pending_tx_packet = NULL;
		m_freem(m);
		m = NULL;
	}
	fakeif->iff_start_busy = TRUE;
	feth_unlock();
	save_m = NULL;
	for (;;) {
		if (copy_m != NULL) {
			assert(peer != NULL);
			feth_output_common(ifp, copy_m, peer, flags);
			copy_m = NULL;
		}
		if (ifnet_dequeue(ifp, &m) != 0) {
			break;
		}
		if (peer == NULL) {
			m_freem(m);
		} else {
			copy_m = copy_mbuf(m);
			if (copy_m == NULL) {
				save_m = m;
				break;
			}
			m_freem(m);
		}
	}
	peer = NULL;
	feth_lock();
	fakeif = ifnet_get_if_fake(ifp);
	if (fakeif != NULL) {
		fakeif->iff_start_busy = FALSE;
		if (save_m != NULL && fakeif->iff_peer != NULL) {
			/* save it for next time */
			fakeif->iff_pending_tx_packet = save_m;
			save_m = NULL;
		}
	}
	feth_unlock();
	if (save_m != NULL) {
		/* didn't save packet, so free it */
		m_freem(save_m);
	}
}