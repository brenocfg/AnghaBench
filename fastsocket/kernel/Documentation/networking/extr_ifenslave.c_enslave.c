#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ifreq {int /*<<< orphan*/  ifr_slave; int /*<<< orphan*/  ifr_name; } ;
struct TYPE_12__ {int ifr_flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  ifr_hwaddr; } ;
struct TYPE_10__ {scalar_t__ ifr_mtu; } ;
struct TYPE_9__ {int ifr_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifr_hwaddr; } ;
struct TYPE_7__ {scalar_t__ ifr_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_ENSLAVE_OLD ; 
 int IFF_SLAVE ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCBONDENSLAVE ; 
 int abi_ver ; 
 int clear_if_addr (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int hwaddr_set ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 TYPE_6__ master_flags ; 
 TYPE_5__ master_hwaddr ; 
 TYPE_4__ master_mtu ; 
 int /*<<< orphan*/  saved_errno ; 
 int /*<<< orphan*/  set_if_addr (char*,char*) ; 
 int set_if_down (char*,int) ; 
 int set_if_up (char*,int) ; 
 int set_master_hwaddr (char*,int /*<<< orphan*/ *) ; 
 int set_slave_hwaddr (char*,int /*<<< orphan*/ *) ; 
 int set_slave_mtu (char*,scalar_t__) ; 
 int /*<<< orphan*/  skfd ; 
 TYPE_3__ slave_flags ; 
 TYPE_2__ slave_hwaddr ; 
 TYPE_1__ slave_mtu ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_print (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enslave(char *master_ifname, char *slave_ifname)
{
	struct ifreq ifr;
	int res = 0;

	if (slave_flags.ifr_flags & IFF_SLAVE) {
		fprintf(stderr,
			"Illegal operation: The specified slave interface "
			"'%s' is already a slave\n",
			slave_ifname);
		return 1;
	}

	res = set_if_down(slave_ifname, slave_flags.ifr_flags);
	if (res) {
		fprintf(stderr,
			"Slave '%s': Error: bring interface down failed\n",
			slave_ifname);
		return res;
	}

	if (abi_ver < 2) {
		/* Older bonding versions would panic if the slave has no IP
		 * address, so get the IP setting from the master.
		 */
		set_if_addr(master_ifname, slave_ifname);
	} else {
		res = clear_if_addr(slave_ifname);
		if (res) {
			fprintf(stderr,
				"Slave '%s': Error: clear address failed\n",
				slave_ifname);
			return res;
		}
	}

	if (master_mtu.ifr_mtu != slave_mtu.ifr_mtu) {
		res = set_slave_mtu(slave_ifname, master_mtu.ifr_mtu);
		if (res) {
			fprintf(stderr,
				"Slave '%s': Error: set MTU failed\n",
				slave_ifname);
			return res;
		}
	}

	if (hwaddr_set) {
		/* Master already has an hwaddr
		 * so set it's hwaddr to the slave
		 */
		if (abi_ver < 1) {
			/* The driver is using an old ABI, so
			 * the application sets the slave's
			 * hwaddr
			 */
			res = set_slave_hwaddr(slave_ifname,
					       &(master_hwaddr.ifr_hwaddr));
			if (res) {
				fprintf(stderr,
					"Slave '%s': Error: set hw address "
					"failed\n",
					slave_ifname);
				goto undo_mtu;
			}

			/* For old ABI the application needs to bring the
			 * slave back up
			 */
			res = set_if_up(slave_ifname, slave_flags.ifr_flags);
			if (res) {
				fprintf(stderr,
					"Slave '%s': Error: bring interface "
					"down failed\n",
					slave_ifname);
				goto undo_slave_mac;
			}
		}
		/* The driver is using a new ABI,
		 * so the driver takes care of setting
		 * the slave's hwaddr and bringing
		 * it up again
		 */
	} else {
		/* No hwaddr for master yet, so
		 * set the slave's hwaddr to it
		 */
		if (abi_ver < 1) {
			/* For old ABI, the master needs to be
			 * down before setting it's hwaddr
			 */
			res = set_if_down(master_ifname, master_flags.ifr_flags);
			if (res) {
				fprintf(stderr,
					"Master '%s': Error: bring interface "
					"down failed\n",
					master_ifname);
				goto undo_mtu;
			}
		}

		res = set_master_hwaddr(master_ifname,
					&(slave_hwaddr.ifr_hwaddr));
		if (res) {
			fprintf(stderr,
				"Master '%s': Error: set hw address "
				"failed\n",
				master_ifname);
			goto undo_mtu;
		}

		if (abi_ver < 1) {
			/* For old ABI, bring the master
			 * back up
			 */
			res = set_if_up(master_ifname, master_flags.ifr_flags);
			if (res) {
				fprintf(stderr,
					"Master '%s': Error: bring interface "
					"up failed\n",
					master_ifname);
				goto undo_master_mac;
			}
		}

		hwaddr_set = 1;
	}

	/* Do the real thing */
	strncpy(ifr.ifr_name, master_ifname, IFNAMSIZ);
	strncpy(ifr.ifr_slave, slave_ifname, IFNAMSIZ);
	if ((ioctl(skfd, SIOCBONDENSLAVE, &ifr) < 0) &&
	    (ioctl(skfd, BOND_ENSLAVE_OLD, &ifr) < 0)) {
		saved_errno = errno;
		v_print("Master '%s': Error: SIOCBONDENSLAVE failed: %s\n",
			master_ifname, strerror(saved_errno));
		res = 1;
	}

	if (res) {
		goto undo_master_mac;
	}

	return 0;

/* rollback (best effort) */
undo_master_mac:
	set_master_hwaddr(master_ifname, &(master_hwaddr.ifr_hwaddr));
	hwaddr_set = 0;
	goto undo_mtu;
undo_slave_mac:
	set_slave_hwaddr(slave_ifname, &(slave_hwaddr.ifr_hwaddr));
undo_mtu:
	set_slave_mtu(slave_ifname, slave_mtu.ifr_mtu);
	return res;
}