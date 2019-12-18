#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sys_sem ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* f ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  net; int /*<<< orphan*/  p; } ;
struct TYPE_6__ {TYPE_2__ cb; TYPE_1__ inp; int /*<<< orphan*/  apimsg; } ;
struct net_msg {int type; TYPE_3__ msg; } ;
typedef  int /*<<< orphan*/  mqmsg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_TIMER_ID ; 
 int ARP_TMR_INTERVAL ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWP_SemPost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMP_TCPIP_MSG ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NETMSG_API 130 
#define  NETMSG_CALLBACK 129 
#define  NETMSG_INPUT 128 
 int TB_MSPERSEC ; 
 int TB_NSPERMS ; 
 int /*<<< orphan*/  TCPIP_DEBUG ; 
 int /*<<< orphan*/  TCP_TIMER_ID ; 
 int TCP_TMR_INTERVAL ; 
 int /*<<< orphan*/  __arp_timer ; 
 void* __lwp_wd_calc_ticks (struct timespec*) ; 
 int /*<<< orphan*/  __lwp_wd_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_insert_ticks (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  __tcp_timer ; 
 int /*<<< orphan*/  apimsg_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arp_time_cntrl ; 
 int /*<<< orphan*/  bba_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etharp_init () ; 
 int /*<<< orphan*/  ip_init () ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct net_msg*) ; 
 void* net_arp_ticks ; 
 void* net_tcp_ticks ; 
 int /*<<< orphan*/  netthread_mbox ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_init () ; 
 int /*<<< orphan*/  tcp_timer_cntrl ; 
 int /*<<< orphan*/  udp_init () ; 

__attribute__((used)) static void* net_thread(void *arg)
{
	struct net_msg *msg;
	struct timespec tb;
	sys_sem sem = (sys_sem)arg;

	etharp_init();
	ip_init();
	udp_init();
	tcp_init();

	tb.tv_sec = ARP_TMR_INTERVAL/TB_MSPERSEC;
	tb.tv_nsec = 0;
	net_arp_ticks = __lwp_wd_calc_ticks(&tb);
	__lwp_wd_initialize(&arp_time_cntrl,__arp_timer,ARP_TIMER_ID,NULL);
	__lwp_wd_insert_ticks(&arp_time_cntrl,net_arp_ticks);

	tb.tv_sec = 0;
	tb.tv_nsec = TCP_TMR_INTERVAL*TB_NSPERMS;
	net_tcp_ticks = __lwp_wd_calc_ticks(&tb);
	__lwp_wd_initialize(&tcp_timer_cntrl,__tcp_timer,TCP_TIMER_ID,NULL);

	LWP_SemPost(sem);

	LWIP_DEBUGF(TCPIP_DEBUG, ("net_thread(%p)\n",arg));

	while(1) {
		MQ_Receive(netthread_mbox,(mqmsg_t)&msg,MQ_MSG_BLOCK);
		switch(msg->type) {
			case NETMSG_API:
			    LWIP_DEBUGF(TCPIP_DEBUG, ("net_thread: API message %p\n", (void *)msg));
				apimsg_input(msg->msg.apimsg);
				break;
			case NETMSG_INPUT:
			    LWIP_DEBUGF(TCPIP_DEBUG, ("net_thread: IP packet %p\n", (void *)msg));
				bba_process(msg->msg.inp.p,msg->msg.inp.net);
				break;
			case NETMSG_CALLBACK:
			    LWIP_DEBUGF(TCPIP_DEBUG, ("net_thread: CALLBACK %p\n", (void *)msg));
				msg->msg.cb.f(msg->msg.cb.ctx);
				break;
			default:
				break;
		}
		memp_free(MEMP_TCPIP_MSG,msg);
	}
	return NULL;
}