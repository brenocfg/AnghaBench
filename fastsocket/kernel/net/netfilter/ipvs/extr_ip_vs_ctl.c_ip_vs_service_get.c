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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct ip_vs_service {int dummy; } ;
typedef  scalar_t__ __u32 ;
typedef  scalar_t__ __u16 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ FTPDATA ; 
 scalar_t__ FTPPORT ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int,union nf_inet_addr const*) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ PROT_SOCK ; 
 struct ip_vs_service* __ip_vs_service_get (int,scalar_t__,union nf_inet_addr const*,scalar_t__) ; 
 struct ip_vs_service* __ip_vs_svc_fwm_get (int,scalar_t__) ; 
 int /*<<< orphan*/  __ip_vs_svc_lock ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_ftpsvc_counter ; 
 int /*<<< orphan*/  ip_vs_nullsvc_counter ; 
 int /*<<< orphan*/  ip_vs_proto_name (scalar_t__) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct ip_vs_service *
ip_vs_service_get(int af, __u32 fwmark, __u16 protocol,
		  const union nf_inet_addr *vaddr, __be16 vport)
{
	struct ip_vs_service *svc;

	read_lock(&__ip_vs_svc_lock);

	/*
	 *	Check the table hashed by fwmark first
	 */
	if (fwmark && (svc = __ip_vs_svc_fwm_get(af, fwmark)))
		goto out;

	/*
	 *	Check the table hashed by <protocol,addr,port>
	 *	for "full" addressed entries
	 */
	svc = __ip_vs_service_get(af, protocol, vaddr, vport);

	if (svc == NULL
	    && protocol == IPPROTO_TCP
	    && atomic_read(&ip_vs_ftpsvc_counter)
	    && (vport == FTPDATA || ntohs(vport) >= PROT_SOCK)) {
		/*
		 * Check if ftp service entry exists, the packet
		 * might belong to FTP data connections.
		 */
		svc = __ip_vs_service_get(af, protocol, vaddr, FTPPORT);
	}

	if (svc == NULL
	    && atomic_read(&ip_vs_nullsvc_counter)) {
		/*
		 * Check if the catch-all port (port zero) exists
		 */
		svc = __ip_vs_service_get(af, protocol, vaddr, 0);
	}

  out:
	read_unlock(&__ip_vs_svc_lock);

	IP_VS_DBG_BUF(9, "lookup service: fwm %u %s %s:%u %s\n",
		      fwmark, ip_vs_proto_name(protocol),
		      IP_VS_DBG_ADDR(af, vaddr), ntohs(vport),
		      svc ? "hit" : "not hit");

	return svc;
}