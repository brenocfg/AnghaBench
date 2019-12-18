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
struct TYPE_5__ {int refCount; int /*<<< orphan*/  flags; scalar_t__ sNum; void* ref; void* parents; void* children; void* searchPath; scalar_t__ nameLen; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  Suff ;

/* Variables and functions */
 int /*<<< orphan*/  Dir_Concat (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LST_CONCLINK ; 
 int /*<<< orphan*/  Lst_Concat (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUFF_NULL ; 
 int /*<<< orphan*/  SuffFree (TYPE_1__*) ; 
 TYPE_1__* bmake_malloc (int) ; 
 int /*<<< orphan*/  bmake_strdup (char*) ; 
 int /*<<< orphan*/  dirSearchPath ; 
 TYPE_1__* emptySuff ; 
 scalar_t__ sNum ; 
 int /*<<< orphan*/  suffClean ; 
 TYPE_1__* suffNull ; 
 void* sufflist ; 

void
Suff_ClearSuffixes(void)
{
#ifdef CLEANUP
    Lst_Concat(suffClean, sufflist, LST_CONCLINK);
#endif
    sufflist = Lst_Init(FALSE);
    sNum = 0;
    if (suffNull)
	SuffFree(suffNull);
    emptySuff = suffNull = bmake_malloc(sizeof(Suff));

    suffNull->name =   	    bmake_strdup("");
    suffNull->nameLen =     0;
    suffNull->searchPath =  Lst_Init(FALSE);
    Dir_Concat(suffNull->searchPath, dirSearchPath);
    suffNull->children =    Lst_Init(FALSE);
    suffNull->parents =	    Lst_Init(FALSE);
    suffNull->ref =	    Lst_Init(FALSE);
    suffNull->sNum =   	    sNum++;
    suffNull->flags =  	    SUFF_NULL;
    suffNull->refCount =    1;
}