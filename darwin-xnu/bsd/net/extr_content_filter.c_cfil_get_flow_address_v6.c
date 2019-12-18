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
typedef  int /*<<< orphan*/  u_int16_t ;
struct in6_addr {int dummy; } ;
struct inpcb {int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; struct in6_addr in6p_faddr; struct in6_addr in6p_laddr; } ;
struct TYPE_4__ {struct in6_addr addr6; } ;
struct TYPE_3__ {struct in6_addr addr6; } ;
struct cfil_hash_entry {int /*<<< orphan*/  cfentry_fport; int /*<<< orphan*/  cfentry_lport; TYPE_2__ cfentry_faddr; TYPE_1__ cfentry_laddr; } ;

/* Variables and functions */

__attribute__((used)) static void
cfil_get_flow_address_v6(struct cfil_hash_entry *entry, struct inpcb *inp,
						 struct in6_addr **laddr, struct in6_addr **faddr,
						 u_int16_t *lport, u_int16_t *fport)
{
	if (entry != NULL) {
		*laddr = &entry->cfentry_laddr.addr6;
		*faddr = &entry->cfentry_faddr.addr6;
		*lport = entry->cfentry_lport;
		*fport = entry->cfentry_fport;
	} else {
		*laddr = &inp->in6p_laddr;
		*faddr = &inp->in6p_faddr;
		*lport = inp->inp_lport;
		*fport = inp->inp_fport;
	}
}