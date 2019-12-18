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
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IP4_ADDR (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ip_input ; 
 int /*<<< orphan*/  loop_netif ; 
 int /*<<< orphan*/  netif_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_loopif_init ; 
 int /*<<< orphan*/  netif_set_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpip_input ; 

void
netif_init(void)
{
#if LWIP_HAVE_LOOPIF
  ip_addr_t loop_ipaddr, loop_netmask, loop_gw;
  IP4_ADDR(&loop_gw, 127,0,0,1);
  IP4_ADDR(&loop_ipaddr, 127,0,0,1);
  IP4_ADDR(&loop_netmask, 255,0,0,0);

#if NO_SYS
  netif_add(&loop_netif, &loop_ipaddr, &loop_netmask, &loop_gw, NULL, netif_loopif_init, ip_input);
#else  /* NO_SYS */
  netif_add(&loop_netif, &loop_ipaddr, &loop_netmask, &loop_gw, NULL, netif_loopif_init, tcpip_input);
#endif /* NO_SYS */
  netif_set_up(&loop_netif);

#endif /* LWIP_HAVE_LOOPIF */
}