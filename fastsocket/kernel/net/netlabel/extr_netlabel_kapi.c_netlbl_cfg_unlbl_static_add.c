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
typedef  int u32 ;
typedef  int u16 ;
struct netlbl_audit {int dummy; } ;
struct net {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EPFNOSUPPORT ; 
 int netlbl_unlhsh_add (struct net*,char const*,void const*,void const*,int,int,struct netlbl_audit*) ; 

int netlbl_cfg_unlbl_static_add(struct net *net,
				const char *dev_name,
				const void *addr,
				const void *mask,
				u16 family,
				u32 secid,
				struct netlbl_audit *audit_info)
{
	u32 addr_len;

	switch (family) {
	case AF_INET:
		addr_len = sizeof(struct in_addr);
		break;
	case AF_INET6:
		addr_len = sizeof(struct in6_addr);
		break;
	default:
		return -EPFNOSUPPORT;
	}

	return netlbl_unlhsh_add(net,
				 dev_name, addr, mask, addr_len,
				 secid, audit_info);
}