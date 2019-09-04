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
struct ifreq {unsigned int ifr_ifindex; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  IF_NAMESIZE ; 
 int /*<<< orphan*/  SIOCGIFNAME ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *if_indextoname(unsigned index, char *name)
{
	struct ifreq ifr;
	int fd, r;

	if ((fd = socket(AF_UNIX, SOCK_DGRAM|SOCK_CLOEXEC, 0)) < 0) return 0;
	ifr.ifr_ifindex = index;
	r = ioctl(fd, SIOCGIFNAME, &ifr);
	__syscall(SYS_close, fd);
	return r < 0 ? 0 : strncpy(name, ifr.ifr_name, IF_NAMESIZE);
}