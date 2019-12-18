#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct svc_serv {struct svc_program* sv_program; } ;
struct svc_program {unsigned int pg_nvers; int /*<<< orphan*/  pg_name; int /*<<< orphan*/  pg_prog; TYPE_1__** pg_vers; struct svc_program* pg_next; } ;
struct TYPE_6__ {TYPE_2__* sighand; } ;
struct TYPE_5__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_4__ {scalar_t__ vs_hidden; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  __svc_unregister (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void svc_unregister(const struct svc_serv *serv)
{
	struct svc_program *progp;
	unsigned long flags;
	unsigned int i;

	clear_thread_flag(TIF_SIGPENDING);

	for (progp = serv->sv_program; progp; progp = progp->pg_next) {
		for (i = 0; i < progp->pg_nvers; i++) {
			if (progp->pg_vers[i] == NULL)
				continue;
			if (progp->pg_vers[i]->vs_hidden)
				continue;

			dprintk("svc: attempting to unregister %sv%u\n",
				progp->pg_name, i);
			__svc_unregister(progp->pg_prog, i, progp->pg_name);
		}
	}

	spin_lock_irqsave(&current->sighand->siglock, flags);
	recalc_sigpending();
	spin_unlock_irqrestore(&current->sighand->siglock, flags);
}