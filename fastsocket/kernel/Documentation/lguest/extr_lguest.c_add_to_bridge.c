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
struct ifreq {char* ifr_name; int ifr_ifindex; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCBRADDIF ; 
 int /*<<< orphan*/  err (int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int if_nametoindex (char const*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void add_to_bridge(int fd, const char *if_name, const char *br_name)
{
	int ifidx;
	struct ifreq ifr;

	if (!*br_name)
		errx(1, "must specify bridge name");

	ifidx = if_nametoindex(if_name);
	if (!ifidx)
		errx(1, "interface %s does not exist!", if_name);

	strncpy(ifr.ifr_name, br_name, IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ-1] = '\0';
	ifr.ifr_ifindex = ifidx;
	if (ioctl(fd, SIOCBRADDIF, &ifr) < 0)
		err(1, "can't add %s to bridge %s", if_name, br_name);
}