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
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_dl {scalar_t__ sdl_alen; } ;
struct mibrcvaddr {int /*<<< orphan*/  flags; } ;
struct mibif {scalar_t__ physaddrlen; int /*<<< orphan*/ * physaddr; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIBRCVADDR_HW ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 struct mibrcvaddr* mib_find_rcvaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct mibrcvaddr* mib_rcvaddr_create (struct mibif*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mib_rcvaddr_delete (struct mibrcvaddr*) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
get_physaddr(struct mibif *ifp, struct sockaddr_dl *sdl, u_char *ptr)
{
	u_char *np;
	struct mibrcvaddr *rcv;

	if (sdl->sdl_alen == 0) {
		/* no address */
		if (ifp->physaddrlen != 0) {
			if ((rcv = mib_find_rcvaddr(ifp->index, ifp->physaddr,
			    ifp->physaddrlen)) != NULL)
				mib_rcvaddr_delete(rcv);
			free(ifp->physaddr);
			ifp->physaddr = NULL;
			ifp->physaddrlen = 0;
		}
		return;
	}

	if (ifp->physaddrlen != sdl->sdl_alen) {
		/* length changed */
		if (ifp->physaddrlen) {
			/* delete olf receive address */
			if ((rcv = mib_find_rcvaddr(ifp->index, ifp->physaddr,
			    ifp->physaddrlen)) != NULL)
				mib_rcvaddr_delete(rcv);
		}
		if ((np = realloc(ifp->physaddr, sdl->sdl_alen)) == NULL) {
			free(ifp->physaddr);
			ifp->physaddr = NULL;
			ifp->physaddrlen = 0;
			return;
		}
		ifp->physaddr = np;
		ifp->physaddrlen = sdl->sdl_alen;

	} else if (memcmp(ifp->physaddr, ptr, ifp->physaddrlen) == 0) {
		/* no change */
		return;

	} else {
		/* address changed */

		/* delete olf receive address */
		if ((rcv = mib_find_rcvaddr(ifp->index, ifp->physaddr,
		    ifp->physaddrlen)) != NULL)
			mib_rcvaddr_delete(rcv);
	}

	memcpy(ifp->physaddr, ptr, ifp->physaddrlen);

	/* make new receive address */
	if ((rcv = mib_rcvaddr_create(ifp, ifp->physaddr, ifp->physaddrlen)) != NULL)
		rcv->flags |= MIBRCVADDR_HW;
}