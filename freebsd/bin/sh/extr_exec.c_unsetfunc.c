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
struct TYPE_2__ {int /*<<< orphan*/  func; } ;
struct tblentry {scalar_t__ cmdtype; TYPE_1__ param; } ;

/* Variables and functions */
 scalar_t__ CMDFUNCTION ; 
 struct tblentry* cmdlookup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_cmd_entry () ; 
 int /*<<< orphan*/  unreffunc (int /*<<< orphan*/ ) ; 

int
unsetfunc(const char *name)
{
	struct tblentry *cmdp;

	if ((cmdp = cmdlookup(name, 0)) != NULL && cmdp->cmdtype == CMDFUNCTION) {
		unreffunc(cmdp->param.func);
		delete_cmd_entry();
		return (0);
	}
	return (0);
}