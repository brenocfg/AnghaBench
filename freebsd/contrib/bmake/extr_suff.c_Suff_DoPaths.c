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
struct TYPE_2__ {int flags; int /*<<< orphan*/  searchPath; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Dir_Concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Dir_CopyDir ; 
 int /*<<< orphan*/  Dir_Destroy ; 
 char* Dir_MakeFlags (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 int SUFF_INCLUDE ; 
 int SUFF_LIBRARY ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Set (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirSearchPath ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sufflist ; 

void
Suff_DoPaths(void)
{
    Suff	   	*s;
    LstNode  		ln;
    char		*ptr;
    Lst	    	    	inIncludes; /* Cumulative .INCLUDES path */
    Lst	    	    	inLibs;	    /* Cumulative .LIBS path */

    if (Lst_Open(sufflist) == FAILURE) {
	return;
    }

    inIncludes = Lst_Init(FALSE);
    inLibs = Lst_Init(FALSE);

    while ((ln = Lst_Next(sufflist)) != NULL) {
	s = (Suff *)Lst_Datum(ln);
	if (!Lst_IsEmpty (s->searchPath)) {
#ifdef INCLUDES
	    if (s->flags & SUFF_INCLUDE) {
		Dir_Concat(inIncludes, s->searchPath);
	    }
#endif /* INCLUDES */
#ifdef LIBRARIES
	    if (s->flags & SUFF_LIBRARY) {
		Dir_Concat(inLibs, s->searchPath);
	    }
#endif /* LIBRARIES */
	    Dir_Concat(s->searchPath, dirSearchPath);
	} else {
	    Lst_Destroy(s->searchPath, Dir_Destroy);
	    s->searchPath = Lst_Duplicate(dirSearchPath, Dir_CopyDir);
	}
    }

    Var_Set(".INCLUDES", ptr = Dir_MakeFlags("-I", inIncludes), VAR_GLOBAL, 0);
    free(ptr);
    Var_Set(".LIBS", ptr = Dir_MakeFlags("-L", inLibs), VAR_GLOBAL, 0);
    free(ptr);

    Lst_Destroy(inIncludes, Dir_Destroy);
    Lst_Destroy(inLibs, Dir_Destroy);

    Lst_Close(sufflist);
}