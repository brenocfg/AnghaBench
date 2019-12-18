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
struct TYPE_4__ {struct TYPE_4__* s; struct TYPE_4__* next; } ;
typedef  TYPE_1__ namelist ;
struct TYPE_5__ {TYPE_1__* nlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int psymb ; 
 TYPE_2__* val ; 

__attribute__((used)) static void
YYDESTRUCT_DECL()
{
    switch (psymb)
    {
	case 263:
#line 30 "inherit2.y"
	{
		  namelist *p = (*val).nlist;
		  while (p != NULL)
		  { namelist *pp = p;
		    p = p->next;
		    free(pp->s); free(pp);
		  }
		}
	break;
#line 441 "inherit2.tab.c"
	case 264:
#line 30 "inherit2.y"
	{
		  namelist *p = (*val).nlist;
		  while (p != NULL)
		  { namelist *pp = p;
		    p = p->next;
		    free(pp->s); free(pp);
		  }
		}
	break;
#line 453 "inherit2.tab.c"
	case 265:
#line 30 "inherit2.y"
	{
		  namelist *p = (*val).nlist;
		  while (p != NULL)
		  { namelist *pp = p;
		    p = p->next;
		    free(pp->s); free(pp);
		  }
		}
	break;
#line 465 "inherit2.tab.c"
    }
}