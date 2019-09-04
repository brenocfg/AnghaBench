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
typedef  int u_long ;
struct proc {int dummy; } ;
struct ifnet {int dummy; } ;
struct if_agentidsreq64 {int /*<<< orphan*/  ifar_uuids; int /*<<< orphan*/  ifar_count; } ;
struct if_agentidsreq32 {int /*<<< orphan*/  ifar_uuids; int /*<<< orphan*/  ifar_count; } ;
struct if_agentidreq {int /*<<< orphan*/  ifar_uuid; } ;
typedef  struct if_agentidsreq64* caddr_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCAIFAGENTID 131 
#define  SIOCDIFAGENTID 130 
#define  SIOCGIFAGENTIDS32 129 
#define  SIOCGIFAGENTIDS64 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct if_agentidsreq64*,struct if_agentidsreq64*,int) ; 
 int if_add_netagent_locked (struct ifnet*,int /*<<< orphan*/ ) ; 
 int if_delete_netagent_locked (struct ifnet*,int /*<<< orphan*/ ) ; 
 int ifioctl_getnetagents (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 int proc_suser (struct proc*) ; 

__attribute__((used)) static __attribute__((noinline)) int
ifioctl_netagent(struct ifnet *ifp, u_long cmd, caddr_t data, struct proc *p)
{
	struct if_agentidreq *ifar = (struct if_agentidreq *)(void *)data;
	union {
		struct if_agentidsreq32 s32;
		struct if_agentidsreq64 s64;
	} u;
	int error = 0;

	VERIFY(ifp != NULL);

	/* Get an io ref count if the interface is attached */
	if (!ifnet_is_attached(ifp, 1)) {
		return (EOPNOTSUPP);
	}

	if (cmd == SIOCAIFAGENTID ||
		cmd == SIOCDIFAGENTID) {
		ifnet_lock_exclusive(ifp);
	} else {
		ifnet_lock_shared(ifp);
	}

	switch (cmd) {
		case SIOCAIFAGENTID: {		/* struct if_agentidreq */
			// TODO: Use priv_check_cred() instead of root check
			if ((error = proc_suser(p)) != 0) {
				break;
			}
			error = if_add_netagent_locked(ifp, ifar->ifar_uuid);
			break;
		}
		case SIOCDIFAGENTID: {			/* struct if_agentidreq */
			// TODO: Use priv_check_cred() instead of root check
			if ((error = proc_suser(p)) != 0) {
				break;
			}
			error = if_delete_netagent_locked(ifp, ifar->ifar_uuid);
			break;
		}
		case SIOCGIFAGENTIDS32: {	/* struct if_agentidsreq32 */
			bcopy(data, &u.s32, sizeof(u.s32));
			error = ifioctl_getnetagents(ifp, &u.s32.ifar_count,
			    u.s32.ifar_uuids);
			if (error == 0) {
				bcopy(&u.s32, data, sizeof(u.s32));
			}
			break;
		}
		case SIOCGIFAGENTIDS64: {	/* struct if_agentidsreq64 */
			bcopy(data, &u.s64, sizeof(u.s64));
			error = ifioctl_getnetagents(ifp, &u.s64.ifar_count,
			    u.s64.ifar_uuids);
			if (error == 0) {
				bcopy(&u.s64, data, sizeof(u.s64));
			}
			break;
		}
		default:
			VERIFY(0);
			/* NOTREACHED */
	}

	ifnet_lock_done(ifp);
	ifnet_decr_iorefcnt(ifp);

	return (error);
}