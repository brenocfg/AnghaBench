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
struct ifreq {int /*<<< orphan*/  ifr_slave; int /*<<< orphan*/  ifr_name; } ;
struct TYPE_2__ {int ifr_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_RELEASE_OLD ; 
 int IFF_SLAVE ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCBONDRELEASE ; 
 int abi_ver ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  saved_errno ; 
 int set_if_down (char*,int) ; 
 int /*<<< orphan*/  set_slave_mtu (char*,int) ; 
 int /*<<< orphan*/  skfd ; 
 TYPE_1__ slave_flags ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_print (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int release(char *master_ifname, char *slave_ifname)
{
	struct ifreq ifr;
	int res = 0;

	if (!(slave_flags.ifr_flags & IFF_SLAVE)) {
		fprintf(stderr,
			"Illegal operation: The specified slave interface "
			"'%s' is not a slave\n",
			slave_ifname);
		return 1;
	}

	strncpy(ifr.ifr_name, master_ifname, IFNAMSIZ);
	strncpy(ifr.ifr_slave, slave_ifname, IFNAMSIZ);
	if ((ioctl(skfd, SIOCBONDRELEASE, &ifr) < 0) &&
	    (ioctl(skfd, BOND_RELEASE_OLD, &ifr) < 0)) {
		saved_errno = errno;
		v_print("Master '%s': Error: SIOCBONDRELEASE failed: %s\n",
			master_ifname, strerror(saved_errno));
		return 1;
	} else if (abi_ver < 1) {
		/* The driver is using an old ABI, so we'll set the interface
		 * down to avoid any conflicts due to same MAC/IP
		 */
		res = set_if_down(slave_ifname, slave_flags.ifr_flags);
		if (res) {
			fprintf(stderr,
				"Slave '%s': Error: bring interface "
				"down failed\n",
				slave_ifname);
		}
	}

	/* set to default mtu */
	set_slave_mtu(slave_ifname, 1500);

	return res;
}