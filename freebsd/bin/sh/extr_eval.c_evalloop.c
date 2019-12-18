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
struct TYPE_2__ {int /*<<< orphan*/  ch2; int /*<<< orphan*/  ch1; } ;
union node {scalar_t__ type; TYPE_1__ nbinary; } ;

/* Variables and functions */
 int EV_TESTED ; 
 scalar_t__ NWHILE ; 
 scalar_t__ SKIPBREAK ; 
 scalar_t__ SKIPCONT ; 
 scalar_t__ SKIPRETURN ; 
 scalar_t__ evalskip ; 
 int /*<<< orphan*/  evaltree (int /*<<< orphan*/ ,int) ; 
 int exitstatus ; 
 int /*<<< orphan*/  loopnest ; 
 scalar_t__ skipcount ; 

__attribute__((used)) static void
evalloop(union node *n, int flags)
{
	int status;

	loopnest++;
	status = 0;
	for (;;) {
		if (!evalskip)
			evaltree(n->nbinary.ch1, EV_TESTED);
		if (evalskip) {
			if (evalskip == SKIPCONT && --skipcount <= 0) {
				evalskip = 0;
				continue;
			}
			if (evalskip == SKIPBREAK && --skipcount <= 0)
				evalskip = 0;
			if (evalskip == SKIPRETURN)
				status = exitstatus;
			break;
		}
		if (n->type == NWHILE) {
			if (exitstatus != 0)
				break;
		} else {
			if (exitstatus == 0)
				break;
		}
		evaltree(n->nbinary.ch2, flags);
		status = exitstatus;
	}
	loopnest--;
	exitstatus = status;
}