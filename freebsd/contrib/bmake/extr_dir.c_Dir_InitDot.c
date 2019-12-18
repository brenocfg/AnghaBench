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
struct TYPE_4__ {int refCount; } ;
typedef  int /*<<< orphan*/  LstNode ;

/* Variables and functions */
 TYPE_1__* Dir_AddDir (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Dir_SetPATH () ; 
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Member (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dot ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  openDirectories ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
Dir_InitDot(void)
{
    if (dot != NULL) {
	LstNode ln;

	/* Remove old entry from openDirectories, but do not destroy. */
	ln = Lst_Member(openDirectories, dot);
	(void)Lst_Remove(openDirectories, ln);
    }

    dot = Dir_AddDir(NULL, ".");

    if (dot == NULL) {
	Error("Cannot open `.' (%s)", strerror(errno));
	exit(1);
    }

    /*
     * We always need to have dot around, so we increment its reference count
     * to make sure it's not destroyed.
     */
    dot->refCount += 1;
    Dir_SetPATH();			/* initialize */
}