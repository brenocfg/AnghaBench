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

/* Variables and functions */
 scalar_t__ gettime () ; 
 scalar_t__ tcpip_time ; 
 scalar_t__ uip_tcp_active_pcbs ; 
 scalar_t__ uip_tcp_tw_pcbs ; 

void tcpip_tmr_needed()
{
	if(!tcpip_time && (uip_tcp_active_pcbs || uip_tcp_tw_pcbs)) {
		tcpip_time = gettime();
	}
}