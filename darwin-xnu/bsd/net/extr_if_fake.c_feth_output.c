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
struct TYPE_3__ {int /*<<< orphan*/  iff_flags; int /*<<< orphan*/ * iff_peer; } ;

/* Variables and functions */
 struct mbuf* copy_mbuf (struct mbuf*) ; 
 int /*<<< orphan*/  feth_lock () ; 
 int /*<<< orphan*/  feth_output_common (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feth_unlock () ; 
 TYPE_1__* ifnet_get_if_fake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_stat_increment_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
feth_output(ifnet_t ifp, struct mbuf * m)
{
	struct mbuf *		copy_m;
	if_fake_ref		fakeif;
	iff_flags_t		flags;
	ifnet_t		peer = NULL;

	if (m == NULL) {
		return (0);
	}
	copy_m = copy_mbuf(m);
	m_freem(m);
	m = NULL;
	if (copy_m == NULL) {
		/* count this as an output error */
		ifnet_stat_increment_out(ifp, 0, 0, 1);
		return (0);
	}
	feth_lock();
	fakeif = ifnet_get_if_fake(ifp);
	if (fakeif != NULL) {
		peer = fakeif->iff_peer;
		flags = fakeif->iff_flags;
	}
	feth_unlock();
	if (peer == NULL) {
		m_freem(copy_m);
		ifnet_stat_increment_out(ifp, 0, 0, 1);
		return (0);
	}
	feth_output_common(ifp, copy_m, peer, flags);
	return (0);
}