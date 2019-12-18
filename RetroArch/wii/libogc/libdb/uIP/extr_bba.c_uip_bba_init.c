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
struct uip_netif {int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ s8_t ;
typedef  int s32_t ;

/* Variables and functions */
 scalar_t__ UIP_ERR_IF ; 
 scalar_t__ UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_NETIF_FLAG_LINK_UP ; 
 scalar_t__ __bba_getlink_state_async () ; 
 int /*<<< orphan*/  bba_arp_tmr ; 
 scalar_t__ bba_dochallengeresponse () ; 
 scalar_t__ bba_probe (struct uip_netif*) ; 
 int /*<<< orphan*/ * bba_recv_pbufs ; 
 int /*<<< orphan*/  gettime () ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  uip_arp_init () ; 
 int /*<<< orphan*/  uip_netif_setup (struct uip_netif*) ; 

s8_t uip_bba_init(struct uip_netif *dev)
{
	s8_t ret;
	s32_t cnt;

	ret = bba_probe(dev);
	if(ret<0) return ret;

	ret = bba_dochallengeresponse();
	if(ret<0) return ret;

	cnt = 0;
	do {
		udelay(500);
		cnt++;
	} while((ret=__bba_getlink_state_async())==0 && cnt<10000);
	if(!ret) return UIP_ERR_IF;

	dev->flags |= UIP_NETIF_FLAG_LINK_UP;
	uip_netif_setup(dev);
	uip_arp_init();

	bba_recv_pbufs = NULL;
	bba_arp_tmr = gettime();

	return UIP_ERR_OK;
}