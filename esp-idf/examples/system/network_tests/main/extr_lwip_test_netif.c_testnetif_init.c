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
struct netif {int mtu; int flags; int /*<<< orphan*/  hwaddr_len; int /*<<< orphan*/  linkoutput; int /*<<< orphan*/  output_ip6; int /*<<< orphan*/  output; int /*<<< orphan*/  hostname; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_LWIP_LOCAL_HOSTNAME ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  ETHARP_HWADDR_LEN ; 
 int NETIF_FLAG_BROADCAST ; 
 int NETIF_FLAG_ETHARP ; 
 int NETIF_FLAG_IGMP ; 
 int NETIF_FLAG_LINK_UP ; 
 int /*<<< orphan*/  NETIF_INIT_SNMP (struct netif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  etharp_output ; 
 int /*<<< orphan*/  ethip6_output ; 
 struct netif* g_last_netif ; 
 int /*<<< orphan*/  snmp_ifType_ethernet_csmacd ; 
 int /*<<< orphan*/  testnetif_output ; 

err_t testnetif_init(struct netif *netif)
{

    g_last_netif = netif;

    netif->hostname = CONFIG_LWIP_LOCAL_HOSTNAME;

    /*
     * Initialize the snmp variables and counters inside the struct netif.
     * The last argument should be replaced with your link speed, in units
     * of bits per second.
     */
    NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100);

    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function an call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
    netif->output = etharp_output;
#if LWIP_IPV6
    netif->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 */
    netif->linkoutput = testnetif_output;
    /* set MAC hardware address length */
    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    /* set MAC hardware address */

    /* maximum transfer unit */
    netif->mtu = 1500;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

#if ESP_LWIP
    #if LWIP_IGMP
  netif->flags |= NETIF_FLAG_IGMP;
#endif
#endif
    return ERR_OK;

}