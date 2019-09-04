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
struct socket {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {TYPE_4__ ia46_addr4; } ;
struct TYPE_12__ {TYPE_5__ addr46; int /*<<< orphan*/  addr6; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {TYPE_1__ ia46_addr4; } ;
struct TYPE_9__ {TYPE_2__ addr46; int /*<<< orphan*/  addr6; } ;
struct cfil_hash_entry {int cfentry_family; int /*<<< orphan*/  cfentry_fport; int /*<<< orphan*/  cfentry_lport; TYPE_6__ cfentry_faddr; TYPE_3__ cfentry_laddr; } ;
typedef  int /*<<< orphan*/  local ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  CFIL_LOG (int,char*,char const*,int /*<<< orphan*/ ,struct cfil_hash_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  MAX_IPv6_STR_LEN ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  inet_ntop (int const,void const*,char*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cfil_hash_entry_log(int level, struct socket *so, struct cfil_hash_entry *entry, uint64_t sockId, const char* msg)
{
    char local[MAX_IPv6_STR_LEN+6];
    char remote[MAX_IPv6_STR_LEN+6];
    const void  *addr;

	// No sock or not UDP, no-op
    if (so == NULL || entry == NULL) {
        return;
    }

    local[0] = remote[0] = 0x0;

    switch (entry->cfentry_family) {
        case AF_INET6:
            addr = &entry->cfentry_laddr.addr6;
            inet_ntop(AF_INET6, addr, local, sizeof(local));
            addr = &entry->cfentry_faddr.addr6;
            inet_ntop(AF_INET6, addr, remote, sizeof(local));
            break;
        case AF_INET:
            addr = &entry->cfentry_laddr.addr46.ia46_addr4.s_addr;
            inet_ntop(AF_INET, addr, local, sizeof(local));
            addr = &entry->cfentry_faddr.addr46.ia46_addr4.s_addr;
            inet_ntop(AF_INET, addr, remote, sizeof(local));
            break;
        default:
            return;
    }
    
	CFIL_LOG(level, "<%s>: <UDP so %llx, entry %p, sockID %llu> lport %d fport %d laddr %s faddr %s",
			 msg,
			 (uint64_t)VM_KERNEL_ADDRPERM(so), entry, sockId,
			 ntohs(entry->cfentry_lport), ntohs(entry->cfentry_fport), local, remote);
}