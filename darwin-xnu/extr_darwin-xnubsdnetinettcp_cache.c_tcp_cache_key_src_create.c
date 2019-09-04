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
struct tcpcb {struct inpcb* t_inpcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
struct tcp_cache_key_src {int /*<<< orphan*/  af; TYPE_2__ faddr; TYPE_1__ laddr; int /*<<< orphan*/  ifp; } ;
struct inpcb {int inp_vflag; int /*<<< orphan*/  inp_faddr; int /*<<< orphan*/  inp_laddr; int /*<<< orphan*/  in6p_faddr; int /*<<< orphan*/  in6p_laddr; int /*<<< orphan*/  inp_last_outifp; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int INP_IPV6 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct tcp_cache_key_src*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tcp_cache_key_src_create(struct tcpcb *tp, struct tcp_cache_key_src *tcks)
{
	struct inpcb *inp = tp->t_inpcb;
	memset(tcks, 0, sizeof(*tcks));

	tcks->ifp = inp->inp_last_outifp;

	if (inp->inp_vflag & INP_IPV6) {
		memcpy(&tcks->laddr.addr6, &inp->in6p_laddr, sizeof(struct in6_addr));
		memcpy(&tcks->faddr.addr6, &inp->in6p_faddr, sizeof(struct in6_addr));
		tcks->af = AF_INET6;
	} else {
		memcpy(&tcks->laddr.addr, &inp->inp_laddr, sizeof(struct in_addr));
		memcpy(&tcks->faddr.addr, &inp->inp_faddr, sizeof(struct in_addr));
		tcks->af = AF_INET;
	}

	return;
}