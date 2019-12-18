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
struct ifreq {char* ifr_name; } ;
struct ifconf {int ifc_len; char* ifc_buf; struct ifreq* ifc_req; } ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  SIOCGIFCONF ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ if_getconfig (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifconf*) ; 
 int mif_flags ; 
 int /*<<< orphan*/  opt_a ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  skfd ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void if_print(char *ifname)
{
	char buff[1024];
	struct ifconf ifc;
	struct ifreq *ifr;
	int i;

	if (ifname == (char *)NULL) {
		ifc.ifc_len = sizeof(buff);
		ifc.ifc_buf = buff;
		if (ioctl(skfd, SIOCGIFCONF, &ifc) < 0) {
			perror("SIOCGIFCONF failed");
			return;
		}

		ifr = ifc.ifc_req;
		for (i = ifc.ifc_len / sizeof(struct ifreq); --i >= 0; ifr++) {
			if (if_getconfig(ifr->ifr_name) < 0) {
				fprintf(stderr,
					"%s: unknown interface.\n",
					ifr->ifr_name);
				continue;
			}

			if (((mif_flags & IFF_UP) == 0) && !opt_a) continue;
			/*ife_print(&ife);*/
		}
	} else {
		if (if_getconfig(ifname) < 0) {
			fprintf(stderr,
				"%s: unknown interface.\n", ifname);
		}
	}
}