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
struct sockaddr {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_multiaddrs; } ;
struct ifmultiaddr {int ifma_flags; int ifma_anoncnt; int ifma_reqcnt; int /*<<< orphan*/  ifma_addr; } ;

/* Variables and functions */
 int ENOENT ; 
 int IFMAF_ANONYMOUS ; 
 int /*<<< orphan*/  IFMA_ADDREF_LOCKED (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_LOCK_SPIN (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_UNLOCK (struct ifmultiaddr*) ; 
 struct ifmultiaddr* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct ifmultiaddr* LIST_NEXT (struct ifmultiaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ifa_equal (struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifma_link ; 

__attribute__((used)) static int
if_addmulti_doesexist(struct ifnet *ifp, const struct sockaddr *sa,
    struct ifmultiaddr **retifma, int anon)
{
	struct ifmultiaddr *ifma;

	for (ifma = LIST_FIRST(&ifp->if_multiaddrs); ifma != NULL;
	    ifma = LIST_NEXT(ifma, ifma_link)) {
		IFMA_LOCK_SPIN(ifma);
		if (!ifa_equal(sa, ifma->ifma_addr)) {
			IFMA_UNLOCK(ifma);
			continue;
		}
		if (anon) {
			VERIFY(!(ifma->ifma_flags & IFMAF_ANONYMOUS) ||
			    ifma->ifma_anoncnt != 0);
			VERIFY((ifma->ifma_flags & IFMAF_ANONYMOUS) ||
			    ifma->ifma_anoncnt == 0);
			ifma->ifma_anoncnt++;
			if (!(ifma->ifma_flags & IFMAF_ANONYMOUS)) {
				VERIFY(ifma->ifma_anoncnt == 1);
				ifma->ifma_flags |= IFMAF_ANONYMOUS;
			}
		}
		if (!anon || ifma->ifma_anoncnt == 1) {
			ifma->ifma_reqcnt++;
			VERIFY(ifma->ifma_reqcnt > 1);
		}
		if (retifma != NULL) {
			*retifma = ifma;
			IFMA_ADDREF_LOCKED(ifma);
		}
		IFMA_UNLOCK(ifma);
		return (0);
	}
	return (ENOENT);
}