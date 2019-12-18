#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct socket {struct sock* sk; } ;
struct TYPE_13__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_6__ sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_9__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_family; int /*<<< orphan*/  sk_protocol; } ;
struct inode_security_struct {int sclass; int /*<<< orphan*/  sid; } ;
struct TYPE_10__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_8__ {scalar_t__ saddr; } ;
struct TYPE_11__ {TYPE_3__ v6info; TYPE_1__ v4info; scalar_t__ family; void* sport; } ;
struct TYPE_12__ {TYPE_4__ net; } ;
struct common_audit_data {TYPE_5__ u; } ;
struct TYPE_14__ {struct inode_security_struct* i_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_AUDIT_DATA_INIT (struct common_audit_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_SOCKET__NODE_BIND ; 
 int /*<<< orphan*/  NET ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  PROT_SOCK ; 
 int /*<<< orphan*/  RAWIP_SOCKET__NODE_BIND ; 
#define  SECCLASS_DCCP_SOCKET 130 
#define  SECCLASS_TCP_SOCKET 129 
#define  SECCLASS_UDP_SOCKET 128 
 int /*<<< orphan*/  SOCKET__BIND ; 
 int /*<<< orphan*/  SOCKET__NAME_BIND ; 
 TYPE_7__* SOCK_INODE (struct socket*) ; 
 int /*<<< orphan*/  TCP_SOCKET__NODE_BIND ; 
 int /*<<< orphan*/  UDP_SOCKET__NODE_BIND ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  current ; 
 void* htons (unsigned short) ; 
 int /*<<< orphan*/  inet_get_local_port_range (int*,int*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,TYPE_6__*) ; 
 unsigned short max (int /*<<< orphan*/ ,int) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int sel_netnode_sid (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int sel_netport_sid (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ *) ; 
 int socket_has_perm (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_socket_bind(struct socket *sock, struct sockaddr *address, int addrlen)
{
	u16 family;
	int err;

	err = socket_has_perm(current, sock, SOCKET__BIND);
	if (err)
		goto out;

	/*
	 * If PF_INET or PF_INET6, check name_bind permission for the port.
	 * Multiple address binding for SCTP is not supported yet: we just
	 * check the first address now.
	 */
	family = sock->sk->sk_family;
	if (family == PF_INET || family == PF_INET6) {
		char *addrp;
		struct inode_security_struct *isec;
		struct common_audit_data ad;
		struct sockaddr_in *addr4 = NULL;
		struct sockaddr_in6 *addr6 = NULL;
		unsigned short snum;
		struct sock *sk = sock->sk;
		u32 sid, node_perm;

		isec = SOCK_INODE(sock)->i_security;

		if (family == PF_INET) {
			addr4 = (struct sockaddr_in *)address;
			snum = ntohs(addr4->sin_port);
			addrp = (char *)&addr4->sin_addr.s_addr;
		} else {
			addr6 = (struct sockaddr_in6 *)address;
			snum = ntohs(addr6->sin6_port);
			addrp = (char *)&addr6->sin6_addr.s6_addr;
		}

		if (snum) {
			int low, high;

			inet_get_local_port_range(&low, &high);

			if (snum < max(PROT_SOCK, low) || snum > high) {
				err = sel_netport_sid(sk->sk_protocol,
						      snum, &sid);
				if (err)
					goto out;
				COMMON_AUDIT_DATA_INIT(&ad, NET);
				ad.u.net.sport = htons(snum);
				ad.u.net.family = family;
				err = avc_has_perm(isec->sid, sid,
						   isec->sclass,
						   SOCKET__NAME_BIND, &ad);
				if (err)
					goto out;
			}
		}

		switch (isec->sclass) {
		case SECCLASS_TCP_SOCKET:
			node_perm = TCP_SOCKET__NODE_BIND;
			break;

		case SECCLASS_UDP_SOCKET:
			node_perm = UDP_SOCKET__NODE_BIND;
			break;

		case SECCLASS_DCCP_SOCKET:
			node_perm = DCCP_SOCKET__NODE_BIND;
			break;

		default:
			node_perm = RAWIP_SOCKET__NODE_BIND;
			break;
		}

		err = sel_netnode_sid(addrp, family, &sid);
		if (err)
			goto out;

		COMMON_AUDIT_DATA_INIT(&ad, NET);
		ad.u.net.sport = htons(snum);
		ad.u.net.family = family;

		if (family == PF_INET)
			ad.u.net.v4info.saddr = addr4->sin_addr.s_addr;
		else
			ipv6_addr_copy(&ad.u.net.v6info.saddr, &addr6->sin6_addr);

		err = avc_has_perm(isec->sid, sid,
				   isec->sclass, node_perm, &ad);
		if (err)
			goto out;
	}
out:
	return err;
}