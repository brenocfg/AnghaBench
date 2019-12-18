#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct socket {TYPE_5__* so_cfil; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_7__ {int /*<<< orphan*/  s6_addr32; } ;
struct inpcb {int inp_vflag; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; TYPE_6__* inp_socket; int /*<<< orphan*/  inp_flags; TYPE_4__ inp_faddr; TYPE_3__ inp_laddr; TYPE_2__ in6p_faddr; TYPE_1__ in6p_laddr; } ;
typedef  int /*<<< orphan*/  local ;
struct TYPE_12__ {int /*<<< orphan*/  so_flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  cfi_sock_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  CFIL_LOG (int,char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 
 int INP_IPV6 ; 
 scalar_t__ IS_UDP (struct socket*) ; 
 int /*<<< orphan*/  MAX_IPv6_STR_LEN ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,void const*,char*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static void
cfil_inp_log(int level, struct socket *so, const char* msg)
{
    struct inpcb *inp = NULL;
    char local[MAX_IPv6_STR_LEN+6];
    char remote[MAX_IPv6_STR_LEN+6];
    const void  *addr;

    if (so == NULL) {
        return;
    }
    
    inp = sotoinpcb(so);
    if (inp == NULL) {
        return;
    }
    
    local[0] = remote[0] = 0x0;

#if INET6
    if (inp->inp_vflag & INP_IPV6) {
        addr = &inp->in6p_laddr.s6_addr32;
        inet_ntop(AF_INET6, addr, local, sizeof(local));
        addr = &inp->in6p_faddr.s6_addr32;
        inet_ntop(AF_INET6, addr, remote, sizeof(local));
    } else
#endif /* INET6 */
    {
        addr = &inp->inp_laddr.s_addr;
        inet_ntop(AF_INET, addr, local, sizeof(local));
        addr = &inp->inp_faddr.s_addr;
        inet_ntop(AF_INET, addr, remote, sizeof(local));
    }

	if (so->so_cfil != NULL)
		CFIL_LOG(level, "<%s>: <%s so %llx - flags 0x%x 0x%x, sockID %llu> lport %d fport %d laddr %s faddr %s",
				 msg, IS_UDP(so) ? "UDP" : "TCP",
				 (uint64_t)VM_KERNEL_ADDRPERM(so), inp->inp_flags, inp->inp_socket->so_flags, so->so_cfil->cfi_sock_id,
				 ntohs(inp->inp_lport), ntohs(inp->inp_fport), local, remote);
	else
		CFIL_LOG(level, "<%s>: <%s so %llx - flags 0x%x 0x%x> lport %d fport %d laddr %s faddr %s",
				 msg, IS_UDP(so) ? "UDP" : "TCP",
				 (uint64_t)VM_KERNEL_ADDRPERM(so), inp->inp_flags, inp->inp_socket->so_flags,
				 ntohs(inp->inp_lport), ntohs(inp->inp_fport), local, remote);
}