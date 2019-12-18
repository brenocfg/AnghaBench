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
typedef  union node {int dummy; } node ;
struct TYPE_2__ {int /*<<< orphan*/  func; } ;
struct cmdentry {scalar_t__ special; TYPE_1__ u; int /*<<< orphan*/  cmdtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDFUNCTION ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  addcmdentry (char const*,struct cmdentry*) ; 
 int /*<<< orphan*/  copyfunc (union node*) ; 

void
defun(const char *name, union node *func)
{
	struct cmdentry entry;

	INTOFF;
	entry.cmdtype = CMDFUNCTION;
	entry.u.func = copyfunc(func);
	entry.special = 0;
	addcmdentry(name, &entry);
	INTON;
}