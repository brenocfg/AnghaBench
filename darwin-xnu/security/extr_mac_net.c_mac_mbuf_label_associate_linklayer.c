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
struct mbuf {int dummy; } ;
struct label {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_label_associate_linklayer ; 

void
mac_mbuf_label_associate_linklayer(struct ifnet *ifp, struct mbuf *mbuf)
{
	struct label *m_label;

	/* ifp must be locked */

	m_label = mac_mbuf_to_label(mbuf);

	MAC_PERFORM(mbuf_label_associate_linklayer, ifp, ifp->if_label, mbuf,
	    m_label);
}