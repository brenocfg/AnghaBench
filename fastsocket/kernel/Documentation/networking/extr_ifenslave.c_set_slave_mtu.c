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
struct ifreq {int ifr_mtu; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCSIFMTU ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  saved_errno ; 
 int /*<<< orphan*/  skfd ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_print (char*,char*,int) ; 

__attribute__((used)) static int set_slave_mtu(char *slave_ifname, int mtu)
{
	struct ifreq ifr;
	int res = 0;

	ifr.ifr_mtu = mtu;
	strncpy(ifr.ifr_name, slave_ifname, IFNAMSIZ);

	res = ioctl(skfd, SIOCSIFMTU, &ifr);
	if (res < 0) {
		saved_errno = errno;
		v_print("Slave '%s': Error: SIOCSIFMTU failed: %s\n",
			slave_ifname, strerror(saved_errno));
	} else {
		v_print("Slave '%s': MTU set to %d.\n", slave_ifname, mtu);
	}

	return res;
}