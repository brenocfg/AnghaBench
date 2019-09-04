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
typedef  scalar_t__ u_int64_t ;
struct pfr_ktable {int pfrkt_flags; int /*<<< orphan*/ ** pfrkt_bytes; int /*<<< orphan*/ ** pfrkt_packets; struct pfr_ktable* pfrkt_root; } ;
struct pfr_kentry {int /*<<< orphan*/ ** pfrke_bytes; int /*<<< orphan*/ ** pfrke_packets; scalar_t__ pfrke_not; } ;
struct pf_addr {int dummy; } ;
typedef  int sa_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int PFR_OP_PASS ; 
 int PFR_OP_XPASS ; 
 int PFR_TFLAG_ACTIVE ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  printf (char*) ; 

void
pfr_update_stats(struct pfr_ktable *kt, struct pf_addr *a, sa_family_t af,
    u_int64_t len, int dir_out, int op_pass, int notrule)
{
	struct pfr_kentry	*ke = NULL;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE) && kt->pfrkt_root != NULL)
		kt = kt->pfrkt_root;
	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return;

	switch (af) {
#if INET
	case AF_INET:
		pfr_sin.sin_addr.s_addr = a->addr32[0];
		ke = (struct pfr_kentry *)rn_match(&pfr_sin, kt->pfrkt_ip4);
		if (ke && KENTRY_RNF_ROOT(ke))
			ke = NULL;
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		bcopy(a, &pfr_sin6.sin6_addr, sizeof (pfr_sin6.sin6_addr));
		ke = (struct pfr_kentry *)rn_match(&pfr_sin6, kt->pfrkt_ip6);
		if (ke && KENTRY_RNF_ROOT(ke))
			ke = NULL;
		break;
#endif /* INET6 */
	default:
		;
	}
	if ((ke == NULL || ke->pfrke_not) != notrule) {
		if (op_pass != PFR_OP_PASS)
			printf("pfr_update_stats: assertion failed.\n");
		op_pass = PFR_OP_XPASS;
	}
	kt->pfrkt_packets[dir_out][op_pass]++;
	kt->pfrkt_bytes[dir_out][op_pass] += len;
	if (ke != NULL && op_pass != PFR_OP_XPASS) {
		ke->pfrke_packets[dir_out][op_pass]++;
		ke->pfrke_bytes[dir_out][op_pass] += len;
	}
}