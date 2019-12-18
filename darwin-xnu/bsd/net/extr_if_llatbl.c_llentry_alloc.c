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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct lltable {int /*<<< orphan*/  llt_af; } ;
struct llentry {int dummy; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_NOARP ; 
 int /*<<< orphan*/  IF_AFDATA_RLOCK (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_AFDATA_RUNLOCK (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_AFDATA_WLOCK (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_AFDATA_WUNLOCK (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLE_ADDREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_EXCLUSIVE ; 
 int /*<<< orphan*/  LLE_WLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 struct llentry* lla_lookup (struct lltable*,int /*<<< orphan*/ ,struct sockaddr*) ; 
 struct llentry* lltable_alloc_entry (struct lltable*,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  lltable_free_entry (struct lltable*,struct llentry*) ; 
 int /*<<< orphan*/  lltable_link_entry (struct lltable*,struct llentry*) ; 

struct llentry *
llentry_alloc(struct ifnet *ifp, struct lltable *lt,
    struct sockaddr_storage *dst)
{
	struct llentry *la, *la_tmp;

	IF_AFDATA_RLOCK(ifp, lt->llt_af);
	la = lla_lookup(lt, LLE_EXCLUSIVE, (struct sockaddr *)dst);
	IF_AFDATA_RUNLOCK(ifp, lt->llt_af);

	if (la != NULL) {
		LLE_ADDREF(la);
		LLE_WUNLOCK(la);
		return (la);
	}

	if ((ifp->if_flags & IFF_NOARP) == 0) {
		la = lltable_alloc_entry(lt, 0, (struct sockaddr *)dst);
		if (la == NULL)
			return (NULL);
		IF_AFDATA_WLOCK(ifp, lt->llt_af);
		LLE_WLOCK(la);
		/* Prefer any existing LLE over newly-created one */
		la_tmp = lla_lookup(lt, LLE_EXCLUSIVE, (struct sockaddr *)dst);
		if (la_tmp == NULL)
			lltable_link_entry(lt, la);
		IF_AFDATA_WUNLOCK(ifp, lt->llt_af);
		if (la_tmp != NULL) {
			lltable_free_entry(lt, la);
			la = la_tmp;
		}
		LLE_ADDREF(la);
		LLE_WUNLOCK(la);
	}

	return (la);
}