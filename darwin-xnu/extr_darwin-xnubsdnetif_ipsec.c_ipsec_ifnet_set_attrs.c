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
struct ifnet_stats_param {int dummy; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFEF_NOAUTOIPV6LL ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int IFF_UP ; 
 int /*<<< orphan*/  bzero (struct ifnet_stats_param*,int) ; 
 int /*<<< orphan*/  ifnet_set_eflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_flags (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ifnet_set_mtu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifnet_set_stat (int /*<<< orphan*/ ,struct ifnet_stats_param*) ; 

__attribute__((used)) static errno_t
ipsec_ifnet_set_attrs(ifnet_t ifp)
{
	/* Set flags and additional information. */
	ifnet_set_mtu(ifp, 1500);
	ifnet_set_flags(ifp, IFF_UP | IFF_MULTICAST | IFF_POINTOPOINT, 0xffff);

	/* The interface must generate its own IPv6 LinkLocal address,
	 * if possible following the recommendation of RFC2472 to the 64bit interface ID
	 */
	ifnet_set_eflags(ifp, IFEF_NOAUTOIPV6LL, IFEF_NOAUTOIPV6LL);

#if !IPSEC_NEXUS
	/* Reset the stats in case as the interface may have been recycled */
	struct ifnet_stats_param stats;
	bzero(&stats, sizeof(struct ifnet_stats_param));
	ifnet_set_stat(ifp, &stats);
#endif // !IPSEC_NEXUS

	return (0);
}