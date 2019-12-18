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
struct sfb_fcl {scalar_t__ cnt; int /*<<< orphan*/  fclist; } ;
struct TYPE_3__ {int /*<<< orphan*/  flow_feedback; } ;
struct sfb {TYPE_1__ sfb_stats; TYPE_2__* sfb_ifp; } ;
struct TYPE_4__ {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_CONVERT_LOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  flowadv_add (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sfb_fclist_append(struct sfb *sp, struct sfb_fcl *fcl)
{
	IFCQ_CONVERT_LOCK(&sp->sfb_ifp->if_snd);
	VERIFY(STAILQ_EMPTY(&fcl->fclist) || fcl->cnt > 0);
	sp->sfb_stats.flow_feedback += fcl->cnt;
	fcl->cnt = 0;

	flowadv_add(&fcl->fclist);
	VERIFY(fcl->cnt == 0 && STAILQ_EMPTY(&fcl->fclist));
}