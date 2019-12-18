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
struct tblentry {scalar_t__ cmdtype; int /*<<< orphan*/  special; TYPE_1__ param; } ;
struct cmdentry {scalar_t__ cmdtype; int /*<<< orphan*/  special; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ CMDFUNCTION ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 struct tblentry* cmdlookup (char const*,int) ; 
 int /*<<< orphan*/  unreffunc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
addcmdentry(const char *name, struct cmdentry *entry)
{
	struct tblentry *cmdp;

	INTOFF;
	cmdp = cmdlookup(name, 1);
	if (cmdp->cmdtype == CMDFUNCTION) {
		unreffunc(cmdp->param.func);
	}
	cmdp->cmdtype = entry->cmdtype;
	cmdp->param = entry->u;
	cmdp->special = entry->special;
	INTON;
}