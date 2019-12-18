#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct netif {int dummy; } ;
struct ip_addr {scalar_t__ addr; } ;
struct in_addr {scalar_t__ s_addr; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/ * dev_s ;
struct TYPE_12__ {scalar_t__ addr; } ;
struct TYPE_11__ {scalar_t__ addr; } ;
struct TYPE_10__ {scalar_t__ addr; } ;
struct TYPE_13__ {TYPE_4__ netmask; TYPE_3__ gw; TYPE_2__ ip_addr; TYPE_1__* dhcp; } ;
struct TYPE_9__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DHCPCOARSE_TIMER_ID ; 
 int /*<<< orphan*/  DHCPFINE_TIMER_ID ; 
 scalar_t__ DHCP_BOUND ; 
 scalar_t__ DHCP_COARSE_TIMER_SECS ; 
 int DHCP_FINE_TIMER_MSECS ; 
 int EINVAL ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int FALSE ; 
 int /*<<< orphan*/  IP4_ADDR (struct ip_addr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MQBOX_SIZE ; 
 scalar_t__ MQ_ERROR_SUCCESSFUL ; 
 scalar_t__ MQ_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TB_NSPERMS ; 
 int TRUE ; 
 int /*<<< orphan*/  __dhcpcoarse_timer ; 
 int /*<<< orphan*/  __dhcpfine_timer ; 
 int /*<<< orphan*/  __lwp_wd_calc_ticks (struct timespec*) ; 
 int /*<<< orphan*/  __lwp_wd_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_insert_ticks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bba_create (TYPE_5__*) ; 
 int /*<<< orphan*/  bba_init ; 
 int /*<<< orphan*/  dhcp_coarsetimer_cntrl ; 
 int /*<<< orphan*/  dhcp_finetimer_cntrl ; 
 int /*<<< orphan*/  dhcp_start (struct netif*) ; 
 TYPE_5__ g_hLoopIF ; 
 TYPE_5__ g_hNetIF ; 
 int g_netinitiated ; 
 int /*<<< orphan*/  loopif_init ; 
 int /*<<< orphan*/  mem_init () ; 
 int /*<<< orphan*/  memp_init () ; 
 int /*<<< orphan*/  net_dhcpcoarse_ticks ; 
 int /*<<< orphan*/  net_dhcpfine_ticks ; 
 int net_init () ; 
 int /*<<< orphan*/  net_input ; 
 struct netif* netif_add (TYPE_5__*,struct ip_addr*,struct ip_addr*,struct ip_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_init () ; 
 int /*<<< orphan*/  netif_set_default (struct netif*) ; 
 int /*<<< orphan*/  netif_set_up (struct netif*) ; 
 int /*<<< orphan*/  netthread_mbox ; 
 int /*<<< orphan*/  pbuf_init () ; 
 int /*<<< orphan*/  stats_init () ; 
 int /*<<< orphan*/  sys_init () ; 
 int /*<<< orphan*/  usleep (int) ; 

s32 if_configex(struct in_addr *local_ip,struct in_addr *netmask,struct in_addr *gateway,bool use_dhcp, int max_retries)
{
	s32 ret = 0;
	struct ip_addr loc_ip, mask, gw;
	struct netif *pnet;
	struct timespec tb;
	dev_s hbba = NULL;

	if(g_netinitiated) return 0;
	g_netinitiated = 1;

//	AddDevice(&dotab_stdnet);
#ifdef STATS
	stats_init();
#endif /* STATS */

	sys_init();
	mem_init();
	memp_init();
	pbuf_init();
	netif_init();

	// init tcpip thread message box
	if(MQ_Init(&netthread_mbox,MQBOX_SIZE)!=MQ_ERROR_SUCCESSFUL) return -1;

	// create & setup interface
	loc_ip.addr = 0;
	mask.addr = 0;
	gw.addr = 0;

	if(use_dhcp==FALSE) {
		if( !gateway || gateway->s_addr==0
			|| !local_ip || local_ip->s_addr==0
			|| !netmask || netmask->s_addr==0 ) return -EINVAL;
			loc_ip.addr = local_ip->s_addr;
			mask.addr = netmask->s_addr;
			gw.addr = gateway->s_addr;
	}
	hbba = bba_create(&g_hNetIF);
	pnet = netif_add(&g_hNetIF,&loc_ip, &mask, &gw, hbba, bba_init, net_input);
	if(pnet) {
		netif_set_up(pnet);
		netif_set_default(pnet);
#if (LWIP_DHCP)
		if(use_dhcp==TRUE) {
			//setup coarse timer
			tb.tv_sec = DHCP_COARSE_TIMER_SECS;
			tb.tv_nsec = 0;
			net_dhcpcoarse_ticks = __lwp_wd_calc_ticks(&tb);
			__lwp_wd_initialize(&dhcp_coarsetimer_cntrl, __dhcpcoarse_timer, DHCPCOARSE_TIMER_ID, NULL);
			__lwp_wd_insert_ticks(&dhcp_coarsetimer_cntrl, net_dhcpcoarse_ticks);

			//setup fine timer
			tb.tv_sec = 0;
			tb.tv_nsec = DHCP_FINE_TIMER_MSECS * TB_NSPERMS;
			net_dhcpfine_ticks = __lwp_wd_calc_ticks(&tb);
			__lwp_wd_initialize(&dhcp_finetimer_cntrl, __dhcpfine_timer, DHCPFINE_TIMER_ID, NULL);
			__lwp_wd_insert_ticks(&dhcp_finetimer_cntrl, net_dhcpfine_ticks);

			//now start dhcp client
			dhcp_start(pnet);
		}
#endif
	} else
		return -ENXIO;

	// setup loopinterface
	IP4_ADDR(&loc_ip, 127, 0, 0, 1);
	IP4_ADDR(&mask, 255, 0, 0, 0);
	IP4_ADDR(&gw, 127, 0, 0, 1);
	pnet = netif_add(&g_hLoopIF, &loc_ip, &mask, &gw, NULL, loopif_init, net_input);

	//last and least start the tcpip layer
	ret = net_init();

	if ( ret == 0 && use_dhcp == TRUE ) {

		int retries = max_retries;
		// wait for dhcp to bind
		while ( g_hNetIF.dhcp->state != DHCP_BOUND && retries > 0 ) {
			retries--;
			usleep(500000);
		}

		if ( retries > 0 ) {
			//copy back network addresses
			if ( local_ip != NULL ) local_ip->s_addr = g_hNetIF.ip_addr.addr;
			if ( gateway != NULL ) gateway->s_addr = g_hNetIF.gw.addr;
			if ( netmask != NULL ) netmask->s_addr = g_hNetIF.netmask.addr;
		} else {
			ret = -ETIMEDOUT;
		}
	}

	return ret;
}