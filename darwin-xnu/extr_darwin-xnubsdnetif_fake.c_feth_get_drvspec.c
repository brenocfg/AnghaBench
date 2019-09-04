#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int u_int32_t ;
struct if_fake_request {int /*<<< orphan*/  iffr_peer_name; } ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/  iffr ;
typedef  TYPE_1__* if_fake_ref ;
struct TYPE_2__ {int /*<<< orphan*/ * iff_peer; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IF_FAKE_G_CMD_GET_PEER 128 
 int /*<<< orphan*/  bzero (struct if_fake_request*,int) ; 
 int copyout (struct if_fake_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  feth_lock () ; 
 int /*<<< orphan*/  feth_unlock () ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
feth_get_drvspec(ifnet_t ifp, u_int32_t cmd, u_int32_t len,
		 user_addr_t user_addr)
{
	int			error = EOPNOTSUPP;
	if_fake_ref		fakeif;
	struct if_fake_request	iffr;
	ifnet_t			peer;

	switch (cmd) {
	case IF_FAKE_G_CMD_GET_PEER:
		if (len < sizeof(iffr)) {
			error = EINVAL;
			break;
		}
		feth_lock();
		fakeif = (if_fake_ref)ifnet_softc(ifp);
		if (fakeif == NULL) {
			feth_unlock();
			error = EOPNOTSUPP;
			break;
		}
		peer = fakeif->iff_peer;
		feth_unlock();
		bzero(&iffr, sizeof(iffr));
		if (peer != NULL) {
			strlcpy(iffr.iffr_peer_name,
				if_name(peer),
				sizeof(iffr.iffr_peer_name));
		}
		error = copyout(&iffr, user_addr, sizeof(iffr));
		break;
	default:
		break;
	}
	return (error);
}