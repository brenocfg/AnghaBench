#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * fname; scalar_t__ lineno; int /*<<< orphan*/ * suffix; void* commands; int /*<<< orphan*/  context; void* order_succ; void* order_pred; void* children; void* parents; void* cohorts; void* iParents; int /*<<< orphan*/ * cmgn; scalar_t__ mtime; scalar_t__ checked; scalar_t__ flags; int /*<<< orphan*/  made; int /*<<< orphan*/ * centurion; scalar_t__* cohort_num; scalar_t__ unmade_cohorts; scalar_t__ unmade; scalar_t__ type; int /*<<< orphan*/ * path; int /*<<< orphan*/ * uname; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Hash_InitTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* Lst_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ OP_LIB ; 
 int /*<<< orphan*/  UNMADE ; 
 int /*<<< orphan*/ * allGNs ; 
 TYPE_1__* bmake_malloc (int) ; 
 int /*<<< orphan*/  bmake_strdup (char const*) ; 

GNode *
Targ_NewGN(const char *name)
{
    GNode *gn;

    gn = bmake_malloc(sizeof(GNode));
    gn->name = bmake_strdup(name);
    gn->uname = NULL;
    gn->path = NULL;
    if (name[0] == '-' && name[1] == 'l') {
	gn->type = OP_LIB;
    } else {
	gn->type = 0;
    }
    gn->unmade =    	0;
    gn->unmade_cohorts = 0;
    gn->cohort_num[0] = 0;
    gn->centurion =    	NULL;
    gn->made = 	    	UNMADE;
    gn->flags = 	0;
    gn->checked =	0;
    gn->mtime =		0;
    gn->cmgn =		NULL;
    gn->iParents =  	Lst_Init(FALSE);
    gn->cohorts =   	Lst_Init(FALSE);
    gn->parents =   	Lst_Init(FALSE);
    gn->children =  	Lst_Init(FALSE);
    gn->order_pred =  	Lst_Init(FALSE);
    gn->order_succ =  	Lst_Init(FALSE);
    Hash_InitTable(&gn->context, 0);
    gn->commands =  	Lst_Init(FALSE);
    gn->suffix =	NULL;
    gn->lineno =	0;
    gn->fname = 	NULL;

#ifdef CLEANUP
    if (allGNs == NULL)
	allGNs = Lst_Init(FALSE);
    Lst_AtEnd(allGNs, gn);
#endif

    return (gn);
}