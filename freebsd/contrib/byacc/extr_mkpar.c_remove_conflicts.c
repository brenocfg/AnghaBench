#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int symbol; int suppressed; scalar_t__ action_code; scalar_t__ prec; scalar_t__ assoc; struct TYPE_4__* next; } ;
typedef  TYPE_1__ action ;

/* Variables and functions */
 scalar_t__ LEFT ; 
 void* NEW2 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ RIGHT ; 
 scalar_t__* RRconflicts ; 
 scalar_t__ RRcount ; 
 scalar_t__ RRtotal ; 
 scalar_t__ SHIFT ; 
 scalar_t__* SRconflicts ; 
 scalar_t__ SRcount ; 
 scalar_t__ SRtotal ; 
 int /*<<< orphan*/  StartBacktrack (TYPE_1__*) ; 
 int /*<<< orphan*/  Value_t ; 
 int final_state ; 
 int nstates ; 
 TYPE_1__** parser ; 

__attribute__((used)) static void
remove_conflicts(void)
{
    int i;
    int symbol;
    action *p, *pref = 0;

    SRtotal = 0;
    RRtotal = 0;
    SRconflicts = NEW2(nstates, Value_t);
    RRconflicts = NEW2(nstates, Value_t);
    for (i = 0; i < nstates; i++)
    {
	SRcount = 0;
	RRcount = 0;
	symbol = -1;
#if defined(YYBTYACC)
	pref = NULL;
#endif
	for (p = parser[i]; p; p = p->next)
	{
	    if (p->symbol != symbol)
	    {
		/* the first parse action for each symbol is the preferred action */
		pref = p;
		symbol = p->symbol;
	    }
	    /* following conditions handle multiple, i.e., conflicting, parse actions */
	    else if (i == final_state && symbol == 0)
	    {
		SRcount++;
		p->suppressed = 1;
		StartBacktrack(pref);
	    }
	    else if (pref != 0 && pref->action_code == SHIFT)
	    {
		if (pref->prec > 0 && p->prec > 0)
		{
		    if (pref->prec < p->prec)
		    {
			pref->suppressed = 2;
			pref = p;
		    }
		    else if (pref->prec > p->prec)
		    {
			p->suppressed = 2;
		    }
		    else if (pref->assoc == LEFT)
		    {
			pref->suppressed = 2;
			pref = p;
		    }
		    else if (pref->assoc == RIGHT)
		    {
			p->suppressed = 2;
		    }
		    else
		    {
			pref->suppressed = 2;
			p->suppressed = 2;
		    }
		}
		else
		{
		    SRcount++;
		    p->suppressed = 1;
		    StartBacktrack(pref);
		}
	    }
	    else
	    {
		RRcount++;
		p->suppressed = 1;
		StartBacktrack(pref);
	    }
	}
	SRtotal += SRcount;
	RRtotal += RRcount;
	SRconflicts[i] = SRcount;
	RRconflicts[i] = RRcount;
    }
}