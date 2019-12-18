#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uchar ;
struct TYPE_4__ {scalar_t__ tp; scalar_t__ bp; TYPE_2__* lp; } ;
typedef  TYPE_1__ Tokenrow ;
struct TYPE_5__ {int wslen; int flag; size_t type; char* t; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ Token ;

/* Variables and functions */
 int XPWS ; 
 char* newstring (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* wstab ; 

void
makespace(Tokenrow *trp)
{
	uchar *tt;
	Token *tp = trp->tp;

	if (tp >= trp->lp)
		return;
	if (tp->wslen) {
		if (tp->flag&XPWS
		 && (wstab[tp->type] || trp->tp>trp->bp && wstab[(tp-1)->type])) {
			tp->wslen = 0;
			return;
		}
		tp->t[-1] = ' ';
		return;
	}
	if (wstab[tp->type] || trp->tp>trp->bp && wstab[(tp-1)->type])
		return;
	tt = newstring(tp->t, tp->len, 1);
	*tt++ = ' ';
	tp->t = tt;
	tp->wslen = 1;
	tp->flag |= XPWS;
}