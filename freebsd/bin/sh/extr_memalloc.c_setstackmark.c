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
struct stackmark {int /*<<< orphan*/  stacknleft; scalar_t__ stacknxt; int /*<<< orphan*/ * stackp; } ;

/* Variables and functions */
 scalar_t__ SPACE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stacknleft ; 
 scalar_t__ stacknxt ; 
 int /*<<< orphan*/ * stackp ; 
 int /*<<< orphan*/  stalloc (int) ; 

void
setstackmark(struct stackmark *mark)
{
	mark->stackp = stackp;
	mark->stacknxt = stacknxt;
	mark->stacknleft = stacknleft;
	/* Ensure this block stays in place. */
	if (stackp != NULL && stacknxt == SPACE(stackp))
		stalloc(1);
}