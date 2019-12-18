#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ip_vs_timeout_user {int tcp_timeout; int tcp_fin_timeout; int udp_timeout; } ;
struct TYPE_4__ {void** timeout_table; } ;
struct TYPE_3__ {void** timeout_table; } ;

/* Variables and functions */
 void* HZ ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int,int,int) ; 
 size_t IP_VS_TCP_S_ESTABLISHED ; 
 size_t IP_VS_TCP_S_FIN_WAIT ; 
 size_t IP_VS_UDP_S_NORMAL ; 
 TYPE_2__ ip_vs_protocol_tcp ; 
 TYPE_1__ ip_vs_protocol_udp ; 

__attribute__((used)) static int ip_vs_set_timeout(struct ip_vs_timeout_user *u)
{
	IP_VS_DBG(2, "Setting timeout tcp:%d tcpfin:%d udp:%d\n",
		  u->tcp_timeout,
		  u->tcp_fin_timeout,
		  u->udp_timeout);

#ifdef CONFIG_IP_VS_PROTO_TCP
	if (u->tcp_timeout) {
		ip_vs_protocol_tcp.timeout_table[IP_VS_TCP_S_ESTABLISHED]
			= u->tcp_timeout * HZ;
	}

	if (u->tcp_fin_timeout) {
		ip_vs_protocol_tcp.timeout_table[IP_VS_TCP_S_FIN_WAIT]
			= u->tcp_fin_timeout * HZ;
	}
#endif

#ifdef CONFIG_IP_VS_PROTO_UDP
	if (u->udp_timeout) {
		ip_vs_protocol_udp.timeout_table[IP_VS_UDP_S_NORMAL]
			= u->udp_timeout * HZ;
	}
#endif
	return 0;
}