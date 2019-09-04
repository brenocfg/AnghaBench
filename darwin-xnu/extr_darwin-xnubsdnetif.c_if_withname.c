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
struct sockaddr_dl {int sdl_nlen; int /*<<< orphan*/  sdl_data; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 struct ifnet* ifunit (char*) ; 

struct ifnet *
if_withname(struct sockaddr *sa)
{
	char ifname[IFNAMSIZ+1];
	struct sockaddr_dl *sdl = (struct sockaddr_dl *)(void *)sa;

	if ((sa->sa_family != AF_LINK) || (sdl->sdl_nlen == 0) ||
	    (sdl->sdl_nlen > IFNAMSIZ))
		return (NULL);

	/*
	 * ifunit wants a null-terminated name.  It may not be null-terminated
	 * in the sockaddr.  We don't want to change the caller's sockaddr,
	 * and there might not be room to put the trailing null anyway, so we
	 * make a local copy that we know we can null terminate safely.
	 */

	bcopy(sdl->sdl_data, ifname, sdl->sdl_nlen);
	ifname[sdl->sdl_nlen] = '\0';
	return (ifunit(ifname));
}