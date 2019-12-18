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
struct netif {int mtu; int flags; int /*<<< orphan*/  l2_buffer_free_notify; int /*<<< orphan*/  hwaddr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHARP_HWADDR_LEN ; 
 int NETIF_FLAG_BROADCAST ; 
 int NETIF_FLAG_ETHARP ; 
 int NETIF_FLAG_IGMP ; 
 int NETIF_FLAG_LINK_UP ; 
 int /*<<< orphan*/  lwip_netif_wifi_free_rx_buffer ; 

__attribute__((used)) static void
low_level_init(struct netif *netif)
{
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

#if !ESP_L2_TO_L3_COPY
    netif->l2_buffer_free_notify = lwip_netif_wifi_free_rx_buffer;
#endif
}