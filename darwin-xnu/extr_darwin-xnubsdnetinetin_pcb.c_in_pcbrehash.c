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
typedef  int /*<<< orphan*/  u_int32_t ;
struct inpcbhead {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct inpcb {size_t inp_hash_element; int inp_flags2; TYPE_1__* inp_pcbinfo; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; TYPE_2__ inp_faddr; } ;
struct TYPE_3__ {struct inpcbhead* ipi_hashbase; int /*<<< orphan*/  ipi_hashmask; } ;

/* Variables and functions */
 int INP2_INHASHLIST ; 
 size_t INP_PCBHASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct inpcbhead*,struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  inp_hash ; 

void
in_pcbrehash(struct inpcb *inp)
{
	struct inpcbhead *head;
	u_int32_t hashkey_faddr;

#if INET6
	if (inp->inp_vflag & INP_IPV6)
		hashkey_faddr = inp->in6p_faddr.s6_addr32[3] /* XXX */;
	else
#endif /* INET6 */
		hashkey_faddr = inp->inp_faddr.s_addr;

	inp->inp_hash_element = INP_PCBHASH(hashkey_faddr, inp->inp_lport,
	    inp->inp_fport, inp->inp_pcbinfo->ipi_hashmask);
	head = &inp->inp_pcbinfo->ipi_hashbase[inp->inp_hash_element];

	if (inp->inp_flags2 & INP2_INHASHLIST) {
		LIST_REMOVE(inp, inp_hash);
		inp->inp_flags2 &= ~INP2_INHASHLIST;
	}

	VERIFY(!(inp->inp_flags2 & INP2_INHASHLIST));
	LIST_INSERT_HEAD(head, inp, inp_hash);
	inp->inp_flags2 |= INP2_INHASHLIST;

#if NECP
	// This call catches updates to the remote addresses
	inp_update_necp_policy(inp, NULL, NULL, 0);
#endif /* NECP */
}