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
typedef  int u_char ;
struct tcphdr {int th_flags; } ;
struct ip6_fw {int fw_ipflg; int fw_tcpf; int fw_tcpnf; } ;

/* Variables and functions */
 int IPV6_FW_IF_TCPEST ; 
 int IPV6_FW_TCPF_ACK ; 
 int IPV6_FW_TCPF_RST ; 
 int IPV6_FW_TCPF_SYN ; 

__attribute__((used)) static int
tcp6flg_match(struct tcphdr *tcp6, struct ip6_fw *f)
{
	u_char		flg_set, flg_clr;
	
	/*
	 * If an established connection is required, reject packets that
	 * have only SYN of RST|ACK|SYN set.  Otherwise, fall through to
	 * other flag requirements.
	 */
	if ((f->fw_ipflg & IPV6_FW_IF_TCPEST) &&
	    ((tcp6->th_flags & (IPV6_FW_TCPF_RST | IPV6_FW_TCPF_ACK |
	    IPV6_FW_TCPF_SYN)) == IPV6_FW_TCPF_SYN))
		return 0;

	flg_set = tcp6->th_flags & f->fw_tcpf;
	flg_clr = tcp6->th_flags & f->fw_tcpnf;

	if (flg_set != f->fw_tcpf)
		return 0;
	if (flg_clr)
		return 0;

	return 1;
}