#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_First (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Append (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var_Delete (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* cur ; 
 int /*<<< orphan*/  dirSearchPath ; 
 TYPE_1__* dot ; 
 TYPE_1__* dotLast ; 

void
Dir_SetPATH(void)
{
    LstNode       ln;		/* a list element */
    Path *p;
    Boolean	  hasLastDot = FALSE;	/* true we should search dot last */

    Var_Delete(".PATH", VAR_GLOBAL);
    
    if (Lst_Open(dirSearchPath) == SUCCESS) {
	if ((ln = Lst_First(dirSearchPath)) != NULL) {
	    p = (Path *)Lst_Datum(ln);
	    if (p == dotLast) {
		hasLastDot = TRUE;
		Var_Append(".PATH", dotLast->name, VAR_GLOBAL);
	    }
	}

	if (!hasLastDot) {
	    if (dot)
		Var_Append(".PATH", dot->name, VAR_GLOBAL);
	    if (cur)
		Var_Append(".PATH", cur->name, VAR_GLOBAL);
	}

	while ((ln = Lst_Next(dirSearchPath)) != NULL) {
	    p = (Path *)Lst_Datum(ln);
	    if (p == dotLast)
		continue;
	    if (p == dot && hasLastDot)
		continue;
	    Var_Append(".PATH", p->name, VAR_GLOBAL);
	}

	if (hasLastDot) {
	    if (dot)
		Var_Append(".PATH", dot->name, VAR_GLOBAL);
	    if (cur)
		Var_Append(".PATH", cur->name, VAR_GLOBAL);
	}
	Lst_Close(dirSearchPath);
    }
}