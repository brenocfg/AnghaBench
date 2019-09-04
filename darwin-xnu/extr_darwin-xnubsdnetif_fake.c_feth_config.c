#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  TYPE_1__* if_fake_ref ;
struct TYPE_4__ {int /*<<< orphan*/ * iff_peer; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FALSE ; 
 int /*<<< orphan*/  KEV_DL_LINK_OFF ; 
 int /*<<< orphan*/  KEV_DL_LINK_ON ; 
 int TRUE ; 
 scalar_t__ feth_is_detaching (TYPE_1__*) ; 
 int /*<<< orphan*/  feth_lock () ; 
 int /*<<< orphan*/  feth_unlock () ; 
 TYPE_1__* ifnet_get_if_fake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_link_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
feth_config(ifnet_t ifp, ifnet_t peer)
{
	int		connected = FALSE;
	int		disconnected = FALSE;
	int		error = 0;
	if_fake_ref 	fakeif = NULL;

	feth_lock();
	fakeif = ifnet_get_if_fake(ifp);
	if (fakeif == NULL) {
		error = EINVAL;
		goto done;
	}
	if (peer != NULL) {
		/* connect to peer */
		if_fake_ref	peer_fakeif;

		peer_fakeif = ifnet_get_if_fake(peer);
		if (peer_fakeif == NULL) {
			error = EINVAL;
			goto done;
		}
		if (feth_is_detaching(fakeif) ||
		    feth_is_detaching(peer_fakeif) ||
		    peer_fakeif->iff_peer != NULL ||
		    fakeif->iff_peer != NULL) {
			error = EBUSY;
			goto done;
		}
		fakeif->iff_peer = peer;
		peer_fakeif->iff_peer = ifp;
		connected = TRUE;
	}
	else if (fakeif->iff_peer != NULL) {
		/* disconnect from peer */
		if_fake_ref	peer_fakeif;

		peer = fakeif->iff_peer;
		peer_fakeif = ifnet_get_if_fake(peer);
		if (peer_fakeif == NULL) {
			/* should not happen */
			error = EINVAL;
			goto done;
		}
		fakeif->iff_peer = NULL;
		peer_fakeif->iff_peer = NULL;
		disconnected = TRUE;
	}

 done:
	feth_unlock();

	/* generate link status event if we connect or disconnect */
	if (connected) {
		interface_link_event(ifp, KEV_DL_LINK_ON);
		interface_link_event(peer, KEV_DL_LINK_ON);
	}
	else if (disconnected) {
		interface_link_event(ifp, KEV_DL_LINK_OFF);
		interface_link_event(peer, KEV_DL_LINK_OFF);
	}
	return (error);
}