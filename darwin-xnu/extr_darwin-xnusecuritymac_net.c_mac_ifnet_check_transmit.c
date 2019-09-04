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
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ,struct mbuf*,struct label*,int,int) ; 
 int /*<<< orphan*/  ifnet_check_transmit ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 

int
mac_ifnet_check_transmit(struct ifnet *ifp, struct mbuf *mbuf, int family,
    int type)
{
	struct label *label;
	int error;

	label = mac_mbuf_to_label(mbuf);

	ifnet_lock_shared(ifp);
	MAC_CHECK(ifnet_check_transmit, ifp, ifp->if_label, mbuf, label,
	    family, type);
	ifnet_lock_done(ifp);

	return (error);
}