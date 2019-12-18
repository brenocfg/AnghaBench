#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* tp; TYPE_2__* lp; } ;
typedef  TYPE_1__ Tokenrow ;
struct TYPE_12__ {scalar_t__ type; int len; scalar_t__ hideset; int /*<<< orphan*/ * t; } ;
typedef  TYPE_2__ Token ;
struct TYPE_13__ {int flag; scalar_t__ val; } ;
typedef  TYPE_3__ Nlist ;

/* Variables and functions */
 scalar_t__ DEFINED ; 
 int /*<<< orphan*/  ERROR ; 
 int ISDEFINED ; 
 int ISMAC ; 
 scalar_t__ KDEFINED ; 
 scalar_t__ LP ; 
 scalar_t__ NAME ; 
 void* NAME1 ; 
 scalar_t__ RP ; 
 int /*<<< orphan*/  builtin (TYPE_1__*,scalar_t__) ; 
 scalar_t__ checkhideset (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  expand (TYPE_1__*,TYPE_3__*) ; 
 TYPE_3__* lookup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ quicklook (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsource (char*,int,char*) ; 
 int /*<<< orphan*/  unsetsource () ; 

void
expandrow(Tokenrow *trp, char *flag)
{
	Token *tp;
	Nlist *np;

	if (flag)
		setsource(flag, -1, "");
	for (tp = trp->tp; tp<trp->lp; ) {
		if (tp->type!=NAME
		 || quicklook(tp->t[0], tp->len>1?tp->t[1]:0)==0
		 || (np = lookup(tp, 0))==NULL
		 || (np->flag&(ISDEFINED|ISMAC))==0
		 || tp->hideset && checkhideset(tp->hideset, np)) {
			tp++;
			continue;
		}
		trp->tp = tp;
		if (np->val==KDEFINED) {
			tp->type = DEFINED;
			if ((tp+1)<trp->lp && (tp+1)->type==NAME)
				(tp+1)->type = NAME1;
			else if ((tp+3)<trp->lp && (tp+1)->type==LP
			 && (tp+2)->type==NAME && (tp+3)->type==RP)
				(tp+2)->type = NAME1;
			else
				error(ERROR, "Incorrect syntax for `defined'");
			tp++;
			continue;
		}
		if (np->flag&ISMAC)
			builtin(trp, np->val);
		else {
			expand(trp, np);
		}
		tp = trp->tp;
	}
	if (flag)
		unsetsource();
}