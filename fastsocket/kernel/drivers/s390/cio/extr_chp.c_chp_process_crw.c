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
struct crw {int erc; int rsid; scalar_t__ slct; int /*<<< orphan*/  anc; int /*<<< orphan*/  rsc; int /*<<< orphan*/  chn; int /*<<< orphan*/  oflw; } ;
struct chp_id {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,int,...) ; 
#define  CRW_ERC_IPARM 130 
#define  CRW_ERC_PERRI 129 
#define  CRW_ERC_PERRN 128 
 int /*<<< orphan*/  chp_id_init (struct chp_id*) ; 
 int /*<<< orphan*/  chp_is_registered (struct chp_id) ; 
 int /*<<< orphan*/  chp_new (struct chp_id) ; 
 int /*<<< orphan*/  chsc_chp_offline (struct chp_id) ; 
 int /*<<< orphan*/  chsc_chp_online (struct chp_id) ; 
 int /*<<< orphan*/  css_schedule_eval_all () ; 

__attribute__((used)) static void chp_process_crw(struct crw *crw0, struct crw *crw1,
			    int overflow)
{
	struct chp_id chpid;

	if (overflow) {
		css_schedule_eval_all();
		return;
	}
	CIO_CRW_EVENT(2, "CRW reports slct=%d, oflw=%d, "
		      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
		      crw0->slct, crw0->oflw, crw0->chn, crw0->rsc, crw0->anc,
		      crw0->erc, crw0->rsid);
	/*
	 * Check for solicited machine checks. These are
	 * created by reset channel path and need not be
	 * handled here.
	 */
	if (crw0->slct) {
		CIO_CRW_EVENT(2, "solicited machine check for "
			      "channel path %02X\n", crw0->rsid);
		return;
	}
	chp_id_init(&chpid);
	chpid.id = crw0->rsid;
	switch (crw0->erc) {
	case CRW_ERC_IPARM: /* Path has come. */
		if (!chp_is_registered(chpid))
			chp_new(chpid);
		chsc_chp_online(chpid);
		break;
	case CRW_ERC_PERRI: /* Path has gone. */
	case CRW_ERC_PERRN:
		chsc_chp_offline(chpid);
		break;
	default:
		CIO_CRW_EVENT(2, "Don't know how to handle erc=%x\n",
			      crw0->erc);
	}
}