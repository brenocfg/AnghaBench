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
struct fileproc {int dummy; } ;
struct fileglob {int fg_lflags; } ;

/* Variables and functions */
 int FG_RMMSGQ ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  closef_locked (struct fileproc*,struct fileglob*,void*) ; 
 void* current_proc () ; 
 int /*<<< orphan*/  fg_removeuipc (struct fileglob*) ; 
 scalar_t__ fg_removeuipc_mark (struct fileglob*) ; 
 int /*<<< orphan*/  proc_fdlock (void*) ; 
 int /*<<< orphan*/  proc_fdunlock (void*) ; 
 int /*<<< orphan*/  unp_disposed ; 
 int /*<<< orphan*/  unp_rights ; 

__attribute__((used)) static void
unp_discard(struct fileglob *fg, void *p)
{
	if (p == NULL)
		p = current_proc();		/* XXX */

	(void) OSAddAtomic(1, &unp_disposed);
	if (fg_removeuipc_mark(fg)) {
		VERIFY(fg->fg_lflags & FG_RMMSGQ);
		fg_removeuipc(fg);
	}
	(void) OSAddAtomic(-1, &unp_rights);

	proc_fdlock(p);
	(void) closef_locked((struct fileproc *)0, fg, p);
	proc_fdunlock(p);
}