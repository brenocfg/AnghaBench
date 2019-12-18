#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int sa_family; scalar_t__ sa_data; } ;
struct TYPE_3__ {int* sa_data; } ;
struct ifreq {int ifr_flags; int ifr_metric; int ifr_mtu; struct sockaddr ifr_netmask; int /*<<< orphan*/  ifr_name; struct sockaddr ifr_broadaddr; struct sockaddr ifr_dstaddr; TYPE_2__ ifr_hwaddr; TYPE_1__ ifr_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFADDR ; 
 int /*<<< orphan*/  SIOCGIFBRDADDR ; 
 int /*<<< orphan*/  SIOCGIFDSTADDR ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCGIFHWADDR ; 
 int /*<<< orphan*/  SIOCGIFMETRIC ; 
 int /*<<< orphan*/  SIOCGIFMTU ; 
 int /*<<< orphan*/  SIOCGIFNETMASK ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 int mif_flags ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  skfd ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int if_getconfig(char *ifname)
{
	struct ifreq ifr;
	int metric, mtu;	/* Parameters of the master interface. */
	struct sockaddr dstaddr, broadaddr, netmask;
	unsigned char *hwaddr;

	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFFLAGS, &ifr) < 0)
		return -1;
	mif_flags = ifr.ifr_flags;
	printf("The result of SIOCGIFFLAGS on %s is %x.\n",
	       ifname, ifr.ifr_flags);

	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFADDR, &ifr) < 0)
		return -1;
	printf("The result of SIOCGIFADDR is %2.2x.%2.2x.%2.2x.%2.2x.\n",
	       ifr.ifr_addr.sa_data[0], ifr.ifr_addr.sa_data[1],
	       ifr.ifr_addr.sa_data[2], ifr.ifr_addr.sa_data[3]);

	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFHWADDR, &ifr) < 0)
		return -1;

	/* Gotta convert from 'char' to unsigned for printf(). */
	hwaddr = (unsigned char *)ifr.ifr_hwaddr.sa_data;
	printf("The result of SIOCGIFHWADDR is type %d  "
	       "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x.\n",
	       ifr.ifr_hwaddr.sa_family, hwaddr[0], hwaddr[1],
	       hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);

	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFMETRIC, &ifr) < 0) {
		metric = 0;
	} else
		metric = ifr.ifr_metric;

	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFMTU, &ifr) < 0)
		mtu = 0;
	else
		mtu = ifr.ifr_mtu;

	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFDSTADDR, &ifr) < 0) {
		memset(&dstaddr, 0, sizeof(struct sockaddr));
	} else
		dstaddr = ifr.ifr_dstaddr;

	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFBRDADDR, &ifr) < 0) {
		memset(&broadaddr, 0, sizeof(struct sockaddr));
	} else
		broadaddr = ifr.ifr_broadaddr;

	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFNETMASK, &ifr) < 0) {
		memset(&netmask, 0, sizeof(struct sockaddr));
	} else
		netmask = ifr.ifr_netmask;

	return 0;
}