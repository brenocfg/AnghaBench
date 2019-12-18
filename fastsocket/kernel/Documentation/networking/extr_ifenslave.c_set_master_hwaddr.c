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
struct sockaddr {scalar_t__ sa_data; } ;
struct ifreq {int /*<<< orphan*/  ifr_hwaddr; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCSIFHWADDR ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 int /*<<< orphan*/  saved_errno ; 
 int /*<<< orphan*/  skfd ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_print (char*,char*,unsigned char,...) ; 

__attribute__((used)) static int set_master_hwaddr(char *master_ifname, struct sockaddr *hwaddr)
{
	unsigned char *addr = (unsigned char *)hwaddr->sa_data;
	struct ifreq ifr;
	int res = 0;

	strncpy(ifr.ifr_name, master_ifname, IFNAMSIZ);
	memcpy(&(ifr.ifr_hwaddr), hwaddr, sizeof(struct sockaddr));
	res = ioctl(skfd, SIOCSIFHWADDR, &ifr);
	if (res < 0) {
		saved_errno = errno;
		v_print("Master '%s': Error: SIOCSIFHWADDR failed: %s\n",
			master_ifname, strerror(saved_errno));
		return res;
	} else {
		v_print("Master '%s': hardware address set to "
			"%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x.\n",
			master_ifname, addr[0], addr[1], addr[2],
			addr[3], addr[4], addr[5]);
	}

	return res;
}