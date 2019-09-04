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
struct in_addr {int dummy; } ;
struct dhcp {struct in_addr dp_yiaddr; } ;
typedef  int /*<<< orphan*/  dhcpol_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTP_RESPONSE ; 
 int /*<<< orphan*/  DHCP_RESPONSE ; 
 int /*<<< orphan*/  FALSE ; 
 void* IOBSDRegistryEntryForDeviceTree (char*) ; 
 void* IOBSDRegistryEntryGetData (void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IOBSDRegistryEntryRelease (void*) ; 
 scalar_t__ dhcpol_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dhcpol_parse_packet (int /*<<< orphan*/ *,struct dhcp const*,int) ; 
 int /*<<< orphan*/  dhcptag_router_e ; 
 int /*<<< orphan*/  dhcptag_subnet_mask_e ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static boolean_t
get_ip_parameters(struct in_addr * iaddr_p, struct in_addr * netmask_p, 
		   struct in_addr * router_p)
{
    void *		entry;
    const void *	pkt;
    int			pkt_len;


    entry = IOBSDRegistryEntryForDeviceTree("/chosen");
    if (entry == NULL) {
	return (FALSE);
    }
    pkt = IOBSDRegistryEntryGetData(entry, DHCP_RESPONSE, &pkt_len);
    if (pkt != NULL && pkt_len >= (int)sizeof(struct dhcp)) {
	printf("netboot: retrieving IP information from DHCP response\n");
    }
    else {
	pkt = IOBSDRegistryEntryGetData(entry, BOOTP_RESPONSE, &pkt_len);
	if (pkt != NULL && pkt_len >= (int)sizeof(struct dhcp)) {
	    printf("netboot: retrieving IP information from BOOTP response\n");
	}
    }
    if (pkt != NULL) {
	const struct in_addr *	ip;
	int			len;
	dhcpol_t 		options;
	const struct dhcp *	reply;

	reply = (const struct dhcp *)pkt;
	(void)dhcpol_parse_packet(&options, reply, pkt_len);
	*iaddr_p = reply->dp_yiaddr;
	ip = (const struct in_addr *)
	    dhcpol_find(&options, 
			dhcptag_subnet_mask_e, &len, NULL);
	if (ip) {
	    *netmask_p = *ip;
	}
	ip = (const struct in_addr *)
	    dhcpol_find(&options, dhcptag_router_e, &len, NULL);
	if (ip) {
	    *router_p = *ip;
	}
    }
    IOBSDRegistryEntryRelease(entry);
    return (pkt != NULL);
}