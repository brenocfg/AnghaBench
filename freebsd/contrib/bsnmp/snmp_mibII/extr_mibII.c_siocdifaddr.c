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
struct in_addr {int dummy; } ;
struct sockaddr_in {int sin_len; struct in_addr sin_addr; int /*<<< orphan*/  sin_family; } ;
struct ifreq {int /*<<< orphan*/  ifr_addr; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  delreq ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SIOCDIFADDR ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mib_netsock ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
siocdifaddr(const char *ifname, struct in_addr addr)
{
	struct ifreq delreq;
	struct sockaddr_in *sa;

	memset(&delreq, 0, sizeof(delreq));
	strlcpy(delreq.ifr_name, ifname, sizeof(delreq.ifr_name));
	sa = (struct sockaddr_in *)(void *)&delreq.ifr_addr;
	sa->sin_family = AF_INET;
	sa->sin_len = sizeof(*sa);
	sa->sin_addr = addr;

	return (ioctl(mib_netsock, SIOCDIFADDR, &delreq));
}