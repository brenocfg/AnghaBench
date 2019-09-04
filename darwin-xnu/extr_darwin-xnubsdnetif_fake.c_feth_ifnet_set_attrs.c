#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ether_header {int dummy; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  TYPE_1__* if_fake_ref ;
struct TYPE_3__ {int iff_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERMTU ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_BROADCAST ; 
 int IFF_FLAGS_HWCSUM ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFNET_CSUM_IP ; 
 int IFNET_CSUM_TCP ; 
 int IFNET_CSUM_TCPIPV6 ; 
 int IFNET_CSUM_UDP ; 
 int IFNET_CSUM_UDPIPV6 ; 
 int /*<<< orphan*/  ifnet_set_addrlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_baudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_capabilities_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifnet_set_flags (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ifnet_set_hdrlen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifnet_set_mtu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_offload (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
feth_ifnet_set_attrs(if_fake_ref fakeif, ifnet_t ifp)
{
	(void)ifnet_set_capabilities_enabled(ifp, 0, -1);
	ifnet_set_addrlen(ifp, ETHER_ADDR_LEN);
	ifnet_set_baudrate(ifp, 0);
	ifnet_set_mtu(ifp, ETHERMTU);
	ifnet_set_flags(ifp,
			IFF_BROADCAST | IFF_MULTICAST | IFF_SIMPLEX,
			0xffff);
	ifnet_set_hdrlen(ifp, sizeof(struct ether_header));
	if ((fakeif->iff_flags & IFF_FLAGS_HWCSUM) != 0) {
		ifnet_set_offload(ifp,
		    IFNET_CSUM_IP | IFNET_CSUM_TCP | IFNET_CSUM_UDP |
		    IFNET_CSUM_TCPIPV6 | IFNET_CSUM_UDPIPV6);
	} else {
		ifnet_set_offload(ifp, 0);
	}
}