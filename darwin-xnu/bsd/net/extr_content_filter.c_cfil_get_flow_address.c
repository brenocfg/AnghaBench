#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct in_addr {int dummy; } ;
struct inpcb {int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; struct in_addr inp_faddr; struct in_addr inp_laddr; } ;
struct TYPE_5__ {struct in_addr ia46_addr4; } ;
struct TYPE_6__ {TYPE_1__ addr46; } ;
struct TYPE_7__ {struct in_addr ia46_addr4; } ;
struct TYPE_8__ {TYPE_3__ addr46; } ;
struct cfil_hash_entry {int /*<<< orphan*/  cfentry_fport; int /*<<< orphan*/  cfentry_lport; TYPE_2__ cfentry_faddr; TYPE_4__ cfentry_laddr; } ;

/* Variables and functions */

__attribute__((used)) static void
cfil_get_flow_address(struct cfil_hash_entry *entry, struct inpcb *inp,
					  struct in_addr *laddr, struct in_addr *faddr,
					  u_int16_t *lport, u_int16_t *fport)
{
	if (entry != NULL) {
		*laddr = entry->cfentry_laddr.addr46.ia46_addr4;
		*faddr = entry->cfentry_faddr.addr46.ia46_addr4;
		*lport = entry->cfentry_lport;
		*fport = entry->cfentry_fport;
	} else {
		*laddr = inp->inp_laddr;
		*faddr = inp->inp_faddr;
		*lport = inp->inp_lport;
		*fport = inp->inp_fport;
	}
}