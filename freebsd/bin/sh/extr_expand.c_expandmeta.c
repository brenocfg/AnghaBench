#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct arglist {int count; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  appendarglist (struct arglist*,char*) ; 
 int /*<<< orphan*/  expdir ; 
 int /*<<< orphan*/  expmeta (int /*<<< orphan*/ ,char*,struct arglist*) ; 
 int /*<<< orphan*/  expsortcmp ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmescapes (char*) ; 

__attribute__((used)) static void
expandmeta(char *pattern, struct arglist *dstlist)
{
	char *p;
	int firstmatch;
	char c;

	firstmatch = dstlist->count;
	p = pattern;
	for (; (c = *p) != '\0'; p++) {
		/* fast check for meta chars */
		if (c == '*' || c == '?' || c == '[') {
			INTOFF;
			expmeta(expdir, pattern, dstlist);
			INTON;
			break;
		}
	}
	if (dstlist->count == firstmatch) {
		/*
		 * no matches
		 */
		rmescapes(pattern);
		appendarglist(dstlist, pattern);
	} else {
		qsort(&dstlist->args[firstmatch],
		    dstlist->count - firstmatch,
		    sizeof(dstlist->args[0]), expsortcmp);
	}
}