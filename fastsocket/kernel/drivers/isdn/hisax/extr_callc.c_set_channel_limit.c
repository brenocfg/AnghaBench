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
struct TYPE_6__ {int (* statcallb ) (TYPE_3__*) ;} ;
struct IsdnCardState {scalar_t__ chanlimit; TYPE_2__ iif; int /*<<< orphan*/  myid; } ;
struct TYPE_5__ {int* num; } ;
struct TYPE_7__ {int arg; TYPE_1__ parm; int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_3__ isdn_ctrl ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISDN_STAT_DISCH ; 
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static int 
set_channel_limit(struct IsdnCardState *cs, int chanmax)
{
	isdn_ctrl ic;
	int i, ii;

	if ((chanmax < 0) || (chanmax > 2))
		return(-EINVAL);
	cs->chanlimit = 0;
	for (ii = 0; ii < 2; ii++) {
		ic.driver = cs->myid;
		ic.command = ISDN_STAT_DISCH;
		ic.arg = ii;
		if (ii >= chanmax)
			ic.parm.num[0] = 0; /* disabled */
		else
			ic.parm.num[0] = 1; /* enabled */
		i = cs->iif.statcallb(&ic); 
		if (i) return(-EINVAL);
		if (ii < chanmax) 
			cs->chanlimit++;
	}
	return(0);
}