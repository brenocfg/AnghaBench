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
struct TYPE_4__ {char* pstr; char* chdname; struct TYPE_4__* fow; scalar_t__ flgs; int /*<<< orphan*/  plen; int /*<<< orphan*/ * pend; } ;
typedef  TYPE_1__ PATTERN ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 TYPE_1__* pathead ; 
 TYPE_1__* pattail ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
pat_add(char *str, char *chdnam)
{
	PATTERN *pt;

	/*
	 * throw out the junk
	 */
	if ((str == NULL) || (*str == '\0')) {
		paxwarn(1, "Empty pattern string");
		return(-1);
	}

	/*
	 * allocate space for the pattern and store the pattern. the pattern is
	 * part of argv so do not bother to copy it, just point at it. Add the
	 * node to the end of the pattern list
	 */
	if ((pt = (PATTERN *)malloc(sizeof(PATTERN))) == NULL) {
		paxwarn(1, "Unable to allocate memory for pattern string");
		return(-1);
	}

	pt->pstr = str;
	pt->pend = NULL;
	pt->plen = strlen(str);
	pt->fow = NULL;
	pt->flgs = 0;
	pt->chdname = chdnam;

	if (pathead == NULL) {
		pattail = pathead = pt;
		return(0);
	}
	pattail->fow = pt;
	pattail = pt;
	return(0);
}