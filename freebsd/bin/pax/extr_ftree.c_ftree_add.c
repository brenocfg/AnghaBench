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
struct TYPE_4__ {char* fname; int chflg; struct TYPE_4__* fow; scalar_t__ refcnt; } ;
typedef  TYPE_1__ FTREE ;

/* Variables and functions */
 TYPE_1__* fthead ; 
 TYPE_1__* fttail ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  paxwarn (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

int
ftree_add(char *str, int chflg)
{
	FTREE *ft;
	int len;

	/*
	 * simple check for bad args
	 */
	if ((str == NULL) || (*str == '\0')) {
		paxwarn(0, "Invalid file name argument");
		return(-1);
	}

	/*
	 * allocate FTREE node and add to the end of the linked list (args are
	 * processed in the same order they were passed to pax). Get rid of any
	 * trailing / the user may pass us. (watch out for / by itself).
	 */
	if ((ft = (FTREE *)malloc(sizeof(FTREE))) == NULL) {
		paxwarn(0, "Unable to allocate memory for filename");
		return(-1);
	}

	if (((len = strlen(str) - 1) > 0) && (str[len] == '/'))
		str[len] = '\0';
	ft->fname = str;
	ft->refcnt = 0;
	ft->chflg = chflg;
	ft->fow = NULL;
	if (fthead == NULL) {
		fttail = fthead = ft;
		return(0);
	}
	fttail->fow = ft;
	fttail = ft;
	return(0);
}