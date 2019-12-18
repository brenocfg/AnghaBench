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
struct tblentry {scalar_t__ cmdtype; } ;

/* Variables and functions */
 scalar_t__ CMDFUNCTION ; 
 struct tblentry* cmdlookup (char const*,int /*<<< orphan*/ ) ; 

int
isfunc(const char *name)
{
	struct tblentry *cmdp;
	cmdp = cmdlookup(name, 0);
	return (cmdp != NULL && cmdp->cmdtype == CMDFUNCTION);
}