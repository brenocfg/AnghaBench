#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int sa_family_t ;
struct TYPE_6__ {int ifr_flags; } ;
struct TYPE_4__ {int sa_family; scalar_t__ sa_data; } ;
struct TYPE_5__ {TYPE_1__ ifr_hwaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EOF ; 
 int IFF_MASTER ; 
 int IFF_UP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int change_active (char*,char*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int enslave (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_drv_info (char*) ; 
 int get_if_settings (char*,int /*<<< orphan*/ ) ; 
 int get_slave_flags (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* help_msg ; 
 int hwaddr_set ; 
 int /*<<< orphan*/  if_print (char*) ; 
 int /*<<< orphan*/  longopts ; 
 TYPE_3__ master_flags ; 
 TYPE_2__ master_hwaddr ; 
 int /*<<< orphan*/  master_ifra ; 
 scalar_t__ opt_V ; 
 scalar_t__ opt_a ; 
 scalar_t__ opt_c ; 
 scalar_t__ opt_d ; 
 int /*<<< orphan*/  opt_f ; 
 scalar_t__ opt_h ; 
 scalar_t__ opt_u ; 
 scalar_t__ opt_v ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int release (char*,char*) ; 
 scalar_t__ skfd ; 
 int /*<<< orphan*/  slave_ifra ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 char* usage_msg ; 
 int /*<<< orphan*/  v_print (char*,char*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,int) ; 
 char* version ; 

int main(int argc, char *argv[])
{
	char **spp, *master_ifname, *slave_ifname;
	int c, i, rv;
	int res = 0;
	int exclusive = 0;

	while ((c = getopt_long(argc, argv, "acdfhuvV", longopts, 0)) != EOF) {
		switch (c) {
		case 'a': opt_a++; exclusive++; break;
		case 'c': opt_c++; exclusive++; break;
		case 'd': opt_d++; exclusive++; break;
		case 'f': opt_f++; exclusive++; break;
		case 'h': opt_h++; exclusive++; break;
		case 'u': opt_u++; exclusive++; break;
		case 'v': opt_v++; break;
		case 'V': opt_V++; exclusive++; break;

		case '?':
			fprintf(stderr, usage_msg);
			res = 2;
			goto out;
		}
	}

	/* options check */
	if (exclusive > 1) {
		fprintf(stderr, usage_msg);
		res = 2;
		goto out;
	}

	if (opt_v || opt_V) {
		printf(version);
		if (opt_V) {
			res = 0;
			goto out;
		}
	}

	if (opt_u) {
		printf(usage_msg);
		res = 0;
		goto out;
	}

	if (opt_h) {
		printf(usage_msg);
		printf(help_msg);
		res = 0;
		goto out;
	}

	/* Open a basic socket */
	if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		res = 1;
		goto out;
	}

	if (opt_a) {
		if (optind == argc) {
			/* No remaining args */
			/* show all interfaces */
			if_print((char *)NULL);
			goto out;
		} else {
			/* Just show usage */
			fprintf(stderr, usage_msg);
			res = 2;
			goto out;
		}
	}

	/* Copy the interface name */
	spp = argv + optind;
	master_ifname = *spp++;

	if (master_ifname == NULL) {
		fprintf(stderr, usage_msg);
		res = 2;
		goto out;
	}

	/* exchange abi version with bonding module */
	res = get_drv_info(master_ifname);
	if (res) {
		fprintf(stderr,
			"Master '%s': Error: handshake with driver failed. "
			"Aborting\n",
			master_ifname);
		goto out;
	}

	slave_ifname = *spp++;

	if (slave_ifname == NULL) {
		if (opt_d || opt_c) {
			fprintf(stderr, usage_msg);
			res = 2;
			goto out;
		}

		/* A single arg means show the
		 * configuration for this interface
		 */
		if_print(master_ifname);
		goto out;
	}

	res = get_if_settings(master_ifname, master_ifra);
	if (res) {
		/* Probably a good reason not to go on */
		fprintf(stderr,
			"Master '%s': Error: get settings failed: %s. "
			"Aborting\n",
			master_ifname, strerror(res));
		goto out;
	}

	/* check if master is indeed a master;
	 * if not then fail any operation
	 */
	if (!(master_flags.ifr_flags & IFF_MASTER)) {
		fprintf(stderr,
			"Illegal operation; the specified interface '%s' "
			"is not a master. Aborting\n",
			master_ifname);
		res = 1;
		goto out;
	}

	/* check if master is up; if not then fail any operation */
	if (!(master_flags.ifr_flags & IFF_UP)) {
		fprintf(stderr,
			"Illegal operation; the specified master interface "
			"'%s' is not up.\n",
			master_ifname);
		res = 1;
		goto out;
	}

	/* Only for enslaving */
	if (!opt_c && !opt_d) {
		sa_family_t master_family = master_hwaddr.ifr_hwaddr.sa_family;
		unsigned char *hwaddr =
			(unsigned char *)master_hwaddr.ifr_hwaddr.sa_data;

		/* The family '1' is ARPHRD_ETHER for ethernet. */
		if (master_family != 1 && !opt_f) {
			fprintf(stderr,
				"Illegal operation: The specified master "
				"interface '%s' is not ethernet-like.\n "
				"This program is designed to work with "
				"ethernet-like network interfaces.\n "
				"Use the '-f' option to force the "
				"operation.\n",
				master_ifname);
			res = 1;
			goto out;
		}

		/* Check master's hw addr */
		for (i = 0; i < 6; i++) {
			if (hwaddr[i] != 0) {
				hwaddr_set = 1;
				break;
			}
		}

		if (hwaddr_set) {
			v_print("current hardware address of master '%s' "
				"is %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x, "
				"type %d\n",
				master_ifname,
				hwaddr[0], hwaddr[1],
				hwaddr[2], hwaddr[3],
				hwaddr[4], hwaddr[5],
				master_family);
		}
	}

	/* Accepts only one slave */
	if (opt_c) {
		/* change active slave */
		res = get_slave_flags(slave_ifname);
		if (res) {
			fprintf(stderr,
				"Slave '%s': Error: get flags failed. "
				"Aborting\n",
				slave_ifname);
			goto out;
		}
		res = change_active(master_ifname, slave_ifname);
		if (res) {
			fprintf(stderr,
				"Master '%s', Slave '%s': Error: "
				"Change active failed\n",
				master_ifname, slave_ifname);
		}
	} else {
		/* Accept multiple slaves */
		do {
			if (opt_d) {
				/* detach a slave interface from the master */
				rv = get_slave_flags(slave_ifname);
				if (rv) {
					/* Can't work with this slave. */
					/* remember the error and skip it*/
					fprintf(stderr,
						"Slave '%s': Error: get flags "
						"failed. Skipping\n",
						slave_ifname);
					res = rv;
					continue;
				}
				rv = release(master_ifname, slave_ifname);
				if (rv) {
					fprintf(stderr,
						"Master '%s', Slave '%s': Error: "
						"Release failed\n",
						master_ifname, slave_ifname);
					res = rv;
				}
			} else {
				/* attach a slave interface to the master */
				rv = get_if_settings(slave_ifname, slave_ifra);
				if (rv) {
					/* Can't work with this slave. */
					/* remember the error and skip it*/
					fprintf(stderr,
						"Slave '%s': Error: get "
						"settings failed: %s. "
						"Skipping\n",
						slave_ifname, strerror(rv));
					res = rv;
					continue;
				}
				rv = enslave(master_ifname, slave_ifname);
				if (rv) {
					fprintf(stderr,
						"Master '%s', Slave '%s': Error: "
						"Enslave failed\n",
						master_ifname, slave_ifname);
					res = rv;
				}
			}
		} while ((slave_ifname = *spp++) != NULL);
	}

out:
	if (skfd >= 0) {
		close(skfd);
	}

	return res;
}