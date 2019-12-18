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
struct ifreq {int ifr_flags; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int IFF_NO_PI ; 
 int IFF_TAP ; 
 int IFF_VNET_HDR ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  TUNSETIFF ; 
 int /*<<< orphan*/  TUNSETNOCSUM ; 
 int /*<<< orphan*/  TUNSETOFFLOAD ; 
 int TUN_F_CSUM ; 
 int TUN_F_TSO4 ; 
 int TUN_F_TSO6 ; 
 int TUN_F_TSO_ECN ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int open_or_die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_tun_device(char tapif[IFNAMSIZ])
{
	struct ifreq ifr;
	int netfd;

	/* Start with this zeroed.  Messy but sure. */
	memset(&ifr, 0, sizeof(ifr));

	/*
	 * We open the /dev/net/tun device and tell it we want a tap device.  A
	 * tap device is like a tun device, only somehow different.  To tell
	 * the truth, I completely blundered my way through this code, but it
	 * works now!
	 */
	netfd = open_or_die("/dev/net/tun", O_RDWR);
	ifr.ifr_flags = IFF_TAP | IFF_NO_PI | IFF_VNET_HDR;
	strcpy(ifr.ifr_name, "tap%d");
	if (ioctl(netfd, TUNSETIFF, &ifr) != 0)
		err(1, "configuring /dev/net/tun");

	if (ioctl(netfd, TUNSETOFFLOAD,
		  TUN_F_CSUM|TUN_F_TSO4|TUN_F_TSO6|TUN_F_TSO_ECN) != 0)
		err(1, "Could not set features for tun device");

	/*
	 * We don't need checksums calculated for packets coming in this
	 * device: trust us!
	 */
	ioctl(netfd, TUNSETNOCSUM, 1);

	memcpy(tapif, ifr.ifr_name, IFNAMSIZ);
	return netfd;
}