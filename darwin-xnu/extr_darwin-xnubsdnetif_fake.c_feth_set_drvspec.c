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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct if_fake_request {char* iffr_peer_name; int /*<<< orphan*/  iffr_dequeue_stall; } ;
typedef  int /*<<< orphan*/ * ifnet_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FAKE_ETHER_NAME ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  IFT_ETHER ; 
#define  IF_FAKE_S_CMD_SET_DEQUEUE_STALL 130 
#define  IF_FAKE_S_CMD_SET_MEDIA 129 
#define  IF_FAKE_S_CMD_SET_PEER 128 
 int feth_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int feth_enable_dequeue_stall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int feth_set_media (int /*<<< orphan*/ *,struct if_fake_request*) ; 
 int if_fake_request_copyin (int /*<<< orphan*/ ,struct if_fake_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifunit (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
feth_set_drvspec(ifnet_t ifp, uint32_t cmd, u_int32_t len,
		 user_addr_t user_addr)
{
	int			error;
	struct if_fake_request	iffr;
	ifnet_t			peer;

	switch (cmd) {
	case IF_FAKE_S_CMD_SET_PEER:
		error = if_fake_request_copyin(user_addr, &iffr, len);
		if (error != 0) {
			break;
		}
		if (iffr.iffr_peer_name[0] == '\0') {
			error = feth_config(ifp, NULL);
			break;
		}

		/* ensure nul termination */
		iffr.iffr_peer_name[IFNAMSIZ - 1] = '\0';
		peer = ifunit(iffr.iffr_peer_name);
		if (peer == NULL) {
			error = ENXIO;
			break;
		}
		if (ifnet_type(peer) != IFT_ETHER) {
			error = EINVAL;
			break;
		}
		if (strcmp(ifnet_name(peer), FAKE_ETHER_NAME) != 0) {
			error = EINVAL;
			break;
		}
		error = feth_config(ifp, peer);
		break;
	case IF_FAKE_S_CMD_SET_MEDIA:
		error = if_fake_request_copyin(user_addr, &iffr, len);
		if (error != 0) {
			break;
		}
		error = feth_set_media(ifp, &iffr);
		break;
	case IF_FAKE_S_CMD_SET_DEQUEUE_STALL:
		error = if_fake_request_copyin(user_addr, &iffr, len);
		if (error != 0) {
			break;
		}
		error = feth_enable_dequeue_stall(ifp,
		    iffr.iffr_dequeue_stall);
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}