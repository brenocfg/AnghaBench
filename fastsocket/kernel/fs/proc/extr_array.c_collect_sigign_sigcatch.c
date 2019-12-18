#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_1__* sighand; } ;
struct TYPE_4__ {scalar_t__ sa_handler; } ;
struct k_sigaction {TYPE_2__ sa; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_3__ {struct k_sigaction* action; } ;

/* Variables and functions */
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int _NSIG ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void collect_sigign_sigcatch(struct task_struct *p, sigset_t *ign,
				    sigset_t *catch)
{
	struct k_sigaction *k;
	int i;

	k = p->sighand->action;
	for (i = 1; i <= _NSIG; ++i, ++k) {
		if (k->sa.sa_handler == SIG_IGN)
			sigaddset(ign, i);
		else if (k->sa.sa_handler != SIG_DFL)
			sigaddset(catch, i);
	}
}