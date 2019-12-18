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
typedef  scalar_t__ u32 ;
typedef  void* s64 ;

/* Variables and functions */
 scalar_t__ UIP_TCP_TMR_INTERVAL ; 
 scalar_t__ diff_msec (void*,void*) ; 
 void* gettime () ; 
 void* tcpip_time ; 
 int /*<<< orphan*/  uip_bba_poll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uip_netif_default ; 
 scalar_t__ uip_tcp_active_pcbs ; 
 int /*<<< orphan*/  uip_tcp_tmr () ; 
 scalar_t__ uip_tcp_tw_pcbs ; 

__attribute__((used)) static void __tcpip_poll()
{
	u32 diff;
	s64 now;

	if(uip_netif_default==NULL) return;

	uip_bba_poll(uip_netif_default);

	if(tcpip_time && (uip_tcp_active_pcbs || uip_tcp_tw_pcbs)) {
		now = gettime();
		diff = diff_msec(tcpip_time,now);
		if(diff>=UIP_TCP_TMR_INTERVAL) {
			uip_tcp_tmr();
			tcpip_time = gettime();
		}
	} else
		tcpip_time = 0;
}