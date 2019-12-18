#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ldc_packet {scalar_t__ stype; scalar_t__ env; int /*<<< orphan*/  seqid; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct ldc_channel {int /*<<< orphan*/  hs_state; int /*<<< orphan*/  snd_nxt; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int LDC_EVENT_UP ; 
 int /*<<< orphan*/  LDC_HS_COMPLETE ; 
 scalar_t__ LDC_INFO ; 
 int /*<<< orphan*/  LDC_STATE_CONNECTED ; 
 int ldc_abort (struct ldc_channel*) ; 
 int /*<<< orphan*/  ldc_set_state (struct ldc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  send_rdx (struct ldc_channel*) ; 

__attribute__((used)) static int process_rtr(struct ldc_channel *lp,
		       struct ldc_packet *p)
{
	ldcdbg(HS, "GOT RTR stype[%x] seqid[%x] env[%x]\n",
	       p->stype, p->seqid, p->env);

	if (p->stype     != LDC_INFO ||
	    p->env       != lp->cfg.mode)
		return ldc_abort(lp);

	lp->snd_nxt = p->seqid;
	lp->hs_state = LDC_HS_COMPLETE;
	ldc_set_state(lp, LDC_STATE_CONNECTED);
	send_rdx(lp);

	return LDC_EVENT_UP;
}