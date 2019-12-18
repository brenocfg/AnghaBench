#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ip_fw_in_args {int dummy; } ;
struct TYPE_6__ {int pkte_npkts; int /*<<< orphan*/  pkte_nbytes; int /*<<< orphan*/ * pkte_tail; struct mbuf* pkte_head; } ;
typedef  TYPE_2__ pktchain_elm_t ;
struct TYPE_7__ {int /*<<< orphan*/  ips_rxc_chainsz_gt4; int /*<<< orphan*/  ips_rxc_chainsz_gt2; } ;

/* Variables and functions */
 int PKTTBL_SZ ; 
 scalar_t__ ip_input_measure ; 
 int /*<<< orphan*/  ip_input_second_pass (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ip_fw_in_args*,int /*<<< orphan*/ ) ; 
 TYPE_3__ ipstat ; 
 int /*<<< orphan*/  net_perf ; 
 int /*<<< orphan*/  net_perf_histogram (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ip_input_second_pass_loop_tbl(pktchain_elm_t *tbl, struct ip_fw_in_args *args)
{
	int i = 0;

	for (i = 0; i < PKTTBL_SZ; i++) {
		if (tbl[i].pkte_head != NULL) {
			struct mbuf *m = tbl[i].pkte_head;
			ip_input_second_pass(m, m->m_pkthdr.rcvif, 0,
			    tbl[i].pkte_npkts, tbl[i].pkte_nbytes, args, 0);

			if (tbl[i].pkte_npkts > 2)
				ipstat.ips_rxc_chainsz_gt2++;
			if (tbl[i].pkte_npkts > 4)
				ipstat.ips_rxc_chainsz_gt4++;
#if (DEBUG || DEVELOPMENT)
			if (ip_input_measure)
				net_perf_histogram(&net_perf, tbl[i].pkte_npkts);
#endif /* (DEBUG || DEVELOPMENT) */
			tbl[i].pkte_head = tbl[i].pkte_tail = NULL;
			tbl[i].pkte_npkts = 0;
			tbl[i].pkte_nbytes = 0;
			/* no need to initialize address and protocol in tbl */
		}
	}
}