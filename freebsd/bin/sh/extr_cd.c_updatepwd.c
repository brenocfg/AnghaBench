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

/* Variables and functions */
 int /*<<< orphan*/  VEXPORT ; 
 int /*<<< orphan*/  ckfree (char*) ; 
 char* curdir ; 
 int /*<<< orphan*/  hashcd () ; 
 char* savestr (char*) ; 
 int /*<<< orphan*/  setvar (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
updatepwd(char *dir)
{
	char *prevdir;

	hashcd();				/* update command hash table */

	setvar("PWD", dir, VEXPORT);
	setvar("OLDPWD", curdir, VEXPORT);
	prevdir = curdir;
	curdir = dir ? savestr(dir) : NULL;
	ckfree(prevdir);
}