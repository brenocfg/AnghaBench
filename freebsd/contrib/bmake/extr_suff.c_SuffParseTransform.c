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
struct TYPE_5__ {int nameLen; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_FindFrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Succ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SuffSuffHasNameP ; 
 int /*<<< orphan*/  SuffSuffIsPrefix ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* suffNull ; 
 int /*<<< orphan*/  sufflist ; 

__attribute__((used)) static Boolean
SuffParseTransform(char *str, Suff **srcPtr, Suff **targPtr)
{
    LstNode		srcLn;	    /* element in suffix list of trans source*/
    Suff		*src;	    /* Source of transformation */
    LstNode		targLn;	    /* element in suffix list of trans target*/
    char		*str2;	    /* Extra pointer (maybe target suffix) */
    LstNode 	    	singleLn;   /* element in suffix list of any suffix
				     * that exactly matches str */
    Suff    	    	*single = NULL;/* Source of possible transformation to
				     * null suffix */

    srcLn = NULL;
    singleLn = NULL;

    /*
     * Loop looking first for a suffix that matches the start of the
     * string and then for one that exactly matches the rest of it. If
     * we can find two that meet these criteria, we've successfully
     * parsed the string.
     */
    for (;;) {
	if (srcLn == NULL) {
	    srcLn = Lst_Find(sufflist, str, SuffSuffIsPrefix);
	} else {
	    srcLn = Lst_FindFrom(sufflist, Lst_Succ(srcLn), str,
				  SuffSuffIsPrefix);
	}
	if (srcLn == NULL) {
	    /*
	     * Ran out of source suffixes -- no such rule
	     */
	    if (singleLn != NULL) {
		/*
		 * Not so fast Mr. Smith! There was a suffix that encompassed
		 * the entire string, so we assume it was a transformation
		 * to the null suffix (thank you POSIX). We still prefer to
		 * find a double rule over a singleton, hence we leave this
		 * check until the end.
		 *
		 * XXX: Use emptySuff over suffNull?
		 */
		*srcPtr = single;
		*targPtr = suffNull;
		return(TRUE);
	    }
	    return (FALSE);
	}
	src = (Suff *)Lst_Datum(srcLn);
	str2 = str + src->nameLen;
	if (*str2 == '\0') {
	    single = src;
	    singleLn = srcLn;
	} else {
	    targLn = Lst_Find(sufflist, str2, SuffSuffHasNameP);
	    if (targLn != NULL) {
		*srcPtr = src;
		*targPtr = (Suff *)Lst_Datum(targLn);
		return (TRUE);
	    }
	}
    }
}