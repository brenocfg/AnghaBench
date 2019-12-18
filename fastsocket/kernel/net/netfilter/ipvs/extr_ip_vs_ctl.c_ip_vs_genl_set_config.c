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
struct nlattr {int dummy; } ;
struct ip_vs_timeout_user {void* udp_timeout; void* tcp_fin_timeout; void* tcp_timeout; } ;

/* Variables and functions */
 size_t IPVS_CMD_ATTR_TIMEOUT_TCP ; 
 size_t IPVS_CMD_ATTR_TIMEOUT_TCP_FIN ; 
 size_t IPVS_CMD_ATTR_TIMEOUT_UDP ; 
 int /*<<< orphan*/  __ip_vs_get_timeouts (struct ip_vs_timeout_user*) ; 
 int ip_vs_set_timeout (struct ip_vs_timeout_user*) ; 
 void* nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int ip_vs_genl_set_config(struct nlattr **attrs)
{
	struct ip_vs_timeout_user t;

	__ip_vs_get_timeouts(&t);

	if (attrs[IPVS_CMD_ATTR_TIMEOUT_TCP])
		t.tcp_timeout = nla_get_u32(attrs[IPVS_CMD_ATTR_TIMEOUT_TCP]);

	if (attrs[IPVS_CMD_ATTR_TIMEOUT_TCP_FIN])
		t.tcp_fin_timeout =
			nla_get_u32(attrs[IPVS_CMD_ATTR_TIMEOUT_TCP_FIN]);

	if (attrs[IPVS_CMD_ATTR_TIMEOUT_UDP])
		t.udp_timeout = nla_get_u32(attrs[IPVS_CMD_ATTR_TIMEOUT_UDP]);

	return ip_vs_set_timeout(&t);
}