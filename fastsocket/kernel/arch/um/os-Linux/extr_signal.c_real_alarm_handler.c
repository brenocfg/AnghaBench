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
struct uml_pt_regs {scalar_t__ is_user; } ;
struct sigcontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGVTALRM ; 
 int /*<<< orphan*/  copy_sc (struct uml_pt_regs*,struct sigcontext*) ; 
 int /*<<< orphan*/  timer_handler (int /*<<< orphan*/ ,struct uml_pt_regs*) ; 
 int /*<<< orphan*/  unblock_signals () ; 

__attribute__((used)) static void real_alarm_handler(struct sigcontext *sc)
{
	struct uml_pt_regs regs;

	if (sc != NULL)
		copy_sc(&regs, sc);
	regs.is_user = 0;
	unblock_signals();
	timer_handler(SIGVTALRM, &regs);
}