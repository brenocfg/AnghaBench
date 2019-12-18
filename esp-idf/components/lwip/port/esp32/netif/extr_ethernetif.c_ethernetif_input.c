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
struct pbuf {void* l2_buf; struct netif* l2_owner; void* payload; } ;
struct netif {scalar_t__ (* input ) (struct pbuf*,struct netif*) ;} ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 int /*<<< orphan*/  PBUF_REF ; 
 int /*<<< orphan*/  ethernet_free_rx_buf_l2 (struct netif*,void*) ; 
 int /*<<< orphan*/  netif_is_up (struct netif*) ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 scalar_t__ stub1 (struct pbuf*,struct netif*) ; 

void ethernetif_input(struct netif *netif, void *buffer, size_t len, void *eb)
{
    struct pbuf *p;

    if (buffer == NULL || !netif_is_up(netif)) {
        if (buffer) {
            ethernet_free_rx_buf_l2(netif, buffer);
        }
        return;
    }

    /* acquire new pbuf, type: PBUF_REF */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_REF);
    if (p == NULL) {
        ethernet_free_rx_buf_l2(netif, buffer);
        return;
    }
    p->payload = buffer;
#if ESP_LWIP
    p->l2_owner = netif;
    p->l2_buf = buffer;
#endif
    /* full packet send to tcpip_thread to process */
    if (netif->input(p, netif) != ERR_OK) {
        LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
        pbuf_free(p);
    }
    /* the pbuf will be free in upper layer, eg: ethernet_input */
}