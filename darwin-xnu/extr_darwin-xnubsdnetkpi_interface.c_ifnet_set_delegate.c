#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_12__ {int type; int family; int subfamily; int expensive; TYPE_1__* ifp; } ;
struct TYPE_13__ {char* if_xname; int if_type; int if_family; int if_subfamily; int if_eflags; TYPE_11__ if_delegated; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int IFEF_ECN_DISABLE ; 
 int IFEF_ECN_ENABLE ; 
 int IFEF_EXPENSIVE ; 
 int /*<<< orphan*/  KEV_DL_IFDELEGATE_CHANGED ; 
 int /*<<< orphan*/  KEV_DL_SUBCLASS ; 
 int /*<<< orphan*/  bzero (TYPE_11__*,int) ; 
 int /*<<< orphan*/  dlil_post_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_is_attached (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_release (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,...) ; 

errno_t
ifnet_set_delegate(ifnet_t ifp, ifnet_t delegated_ifp)
{
	ifnet_t odifp = NULL;

	if (ifp == NULL)
		return (EINVAL);
	else if (!ifnet_is_attached(ifp, 1))
		return (ENXIO);

	ifnet_lock_exclusive(ifp);
	odifp = ifp->if_delegated.ifp;
	if (odifp != NULL && odifp == delegated_ifp) {
		/* delegate info is unchanged; nothing more to do */
		ifnet_lock_done(ifp);
		goto done;
	}
	// Test if this delegate interface would cause a loop
	ifnet_t delegate_check_ifp = delegated_ifp;
	while (delegate_check_ifp != NULL) {
		if (delegate_check_ifp == ifp) {
			printf("%s: delegating to %s would cause a loop\n",
			    ifp->if_xname, delegated_ifp->if_xname);
			ifnet_lock_done(ifp);
			goto done;
		}
		delegate_check_ifp = delegate_check_ifp->if_delegated.ifp;
	}
	bzero(&ifp->if_delegated, sizeof (ifp->if_delegated));
	if (delegated_ifp != NULL && ifp != delegated_ifp) {
		ifp->if_delegated.ifp = delegated_ifp;
		ifnet_reference(delegated_ifp);
		ifp->if_delegated.type = delegated_ifp->if_type;
		ifp->if_delegated.family = delegated_ifp->if_family;
		ifp->if_delegated.subfamily = delegated_ifp->if_subfamily;
		ifp->if_delegated.expensive =
		    delegated_ifp->if_eflags & IFEF_EXPENSIVE ? 1 : 0;

		/*
		 * Propogate flags related to ECN from delegated interface
		 */
		ifp->if_eflags &= ~(IFEF_ECN_ENABLE|IFEF_ECN_DISABLE);
		ifp->if_eflags |= (delegated_ifp->if_eflags &
		    (IFEF_ECN_ENABLE|IFEF_ECN_DISABLE));

		printf("%s: is now delegating %s (type 0x%x, family %u, "
		    "sub-family %u)\n", ifp->if_xname, delegated_ifp->if_xname,
		    delegated_ifp->if_type, delegated_ifp->if_family,
		    delegated_ifp->if_subfamily);
	}

	ifnet_lock_done(ifp);

	if (odifp != NULL) {
		if (odifp != delegated_ifp) {
			printf("%s: is no longer delegating %s\n",
			    ifp->if_xname, odifp->if_xname);
		}
		ifnet_release(odifp);
	}

	/* Generate a kernel event */
	dlil_post_msg(ifp, KEV_DL_SUBCLASS, KEV_DL_IFDELEGATE_CHANGED, NULL, 0);

done:
	/* Release the io ref count */
	ifnet_decr_iorefcnt(ifp);

	return (0);
}