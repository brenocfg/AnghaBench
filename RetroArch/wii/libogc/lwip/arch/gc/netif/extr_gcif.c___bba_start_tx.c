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
struct pbuf {int dummy; } ;
struct netif {int dummy; } ;
struct ip_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWP_GetSelf () ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int /*<<< orphan*/  etharp_output (struct netif*,struct ip_addr*,struct pbuf*) ; 

__attribute__((used)) static err_t __bba_start_tx(struct netif *dev,struct pbuf *p,struct ip_addr *ipaddr)
{
	LWIP_DEBUGF(NETIF_DEBUG,("__bba_start_tx(%p)\n",LWP_GetSelf()));
	return etharp_output(dev,ipaddr,p);
}