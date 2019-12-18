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
typedef  int u16 ;
struct netlbl_audit {int dummy; } ;

/* Variables and functions */
#define  AF_INET 128 
 int EINVAL ; 
 int EPFNOSUPPORT ; 
 int netlbl_domhsh_remove (char const*,struct netlbl_audit*) ; 
 int netlbl_domhsh_remove_af4 (char const*,void const*,void const*,struct netlbl_audit*) ; 

int netlbl_cfg_map_del(const char *domain,
		       u16 family,
		       const void *addr,
		       const void *mask,
		       struct netlbl_audit *audit_info)
{
	if (addr == NULL && mask == NULL) {
		return netlbl_domhsh_remove(domain, audit_info);
	} else if (addr != NULL && mask != NULL) {
		switch (family) {
		case AF_INET:
			return netlbl_domhsh_remove_af4(domain, addr, mask,
							audit_info);
		default:
			return -EPFNOSUPPORT;
		}
	} else
		return -EINVAL;
}