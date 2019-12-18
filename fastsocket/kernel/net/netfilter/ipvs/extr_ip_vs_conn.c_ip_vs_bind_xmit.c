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
struct ip_vs_conn {int /*<<< orphan*/  packet_xmit; } ;

/* Variables and functions */
#define  IP_VS_CONN_F_BYPASS 132 
#define  IP_VS_CONN_F_DROUTE 131 
#define  IP_VS_CONN_F_LOCALNODE 130 
#define  IP_VS_CONN_F_MASQ 129 
#define  IP_VS_CONN_F_TUNNEL 128 
 int IP_VS_FWD_METHOD (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_bypass_xmit ; 
 int /*<<< orphan*/  ip_vs_dr_xmit ; 
 int /*<<< orphan*/  ip_vs_nat_xmit ; 
 int /*<<< orphan*/  ip_vs_null_xmit ; 
 int /*<<< orphan*/  ip_vs_tunnel_xmit ; 

__attribute__((used)) static inline void ip_vs_bind_xmit(struct ip_vs_conn *cp)
{
	switch (IP_VS_FWD_METHOD(cp)) {
	case IP_VS_CONN_F_MASQ:
		cp->packet_xmit = ip_vs_nat_xmit;
		break;

	case IP_VS_CONN_F_TUNNEL:
		cp->packet_xmit = ip_vs_tunnel_xmit;
		break;

	case IP_VS_CONN_F_DROUTE:
		cp->packet_xmit = ip_vs_dr_xmit;
		break;

	case IP_VS_CONN_F_LOCALNODE:
		cp->packet_xmit = ip_vs_null_xmit;
		break;

	case IP_VS_CONN_F_BYPASS:
		cp->packet_xmit = ip_vs_bypass_xmit;
		break;
	}
}