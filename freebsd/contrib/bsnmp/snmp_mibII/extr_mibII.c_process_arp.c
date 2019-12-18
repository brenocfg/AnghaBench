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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr_dl {int /*<<< orphan*/  sdl_alen; scalar_t__ sdl_nlen; scalar_t__ sdl_data; int /*<<< orphan*/  sdl_index; } ;
struct TYPE_2__ {scalar_t__ rmx_expire; } ;
struct rt_msghdr {TYPE_1__ rtm_rmx; } ;
struct mibif {int dummy; } ;
struct mibarp {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIBARP_FOUND ; 
 int /*<<< orphan*/  MIBARP_PERM ; 
 struct mibarp* mib_arp_create (struct mibif*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mibarp* mib_find_arp (struct mibif*,int /*<<< orphan*/ ) ; 
 struct mibif* mib_find_if_sys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_arp(const struct rt_msghdr *rtm, const struct sockaddr_dl *sdl,
    const struct sockaddr_in *sa)
{
	struct mibif *ifp;
	struct mibarp *at;

	/* IP arp table entry */
	if (sdl->sdl_alen == 0)
		return;
	if ((ifp = mib_find_if_sys(sdl->sdl_index)) == NULL)
		return;
	/* have a valid entry */
	if ((at = mib_find_arp(ifp, sa->sin_addr)) == NULL &&
	    (at = mib_arp_create(ifp, sa->sin_addr,
	    sdl->sdl_data + sdl->sdl_nlen, sdl->sdl_alen)) == NULL)
		return;

	if (rtm->rtm_rmx.rmx_expire == 0)
		at->flags |= MIBARP_PERM;
	else
		at->flags &= ~MIBARP_PERM;
	at->flags |= MIBARP_FOUND;
}