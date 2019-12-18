#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int malloc; int nparam; char** p; int reset; int /*<<< orphan*/ * optnext; int /*<<< orphan*/ * optp; } ;

/* Variables and functions */
 char** ckmalloc (int) ; 
 int /*<<< orphan*/  freeparam (TYPE_1__*) ; 
 int /*<<< orphan*/  savestr (int /*<<< orphan*/ ) ; 
 TYPE_1__ shellparam ; 

__attribute__((used)) static void
setparam(int argc, char **argv)
{
	char **newparam;
	char **ap;

	ap = newparam = ckmalloc((argc + 1) * sizeof *ap);
	while (*argv) {
		*ap++ = savestr(*argv++);
	}
	*ap = NULL;
	freeparam(&shellparam);
	shellparam.malloc = 1;
	shellparam.nparam = argc;
	shellparam.p = newparam;
	shellparam.optp = NULL;
	shellparam.reset = 1;
	shellparam.optnext = NULL;
}