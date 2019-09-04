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
struct ctx {int err; int /*<<< orphan*/  sid; int /*<<< orphan*/  eid; int /*<<< orphan*/  id; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SYS_getpid ; 
 int /*<<< orphan*/  SYS_kill ; 
 int /*<<< orphan*/  __block_all_sigs (int /*<<< orphan*/ ) ; 
 int __syscall (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void do_setxid(void *p)
{
	struct ctx *c = p;
	if (c->err>0) return;
#ifdef __EMSCRIPTEN__
	c->err = EPERM; // we don't allow dynamic syscalls, and don't need to support these anyhow
	return;
#else
	int ret = -__syscall(c->nr, c->id, c->eid, c->sid);
	if (ret && !c->err) {
		/* If one thread fails to set ids after another has already
		 * succeeded, forcibly killing the process is the only safe
		 * thing to do. State is inconsistent and dangerous. Use
		 * SIGKILL because it is uncatchable. */
		__block_all_sigs(0);
		__syscall(SYS_kill, __syscall(SYS_getpid), SIGKILL);
	}
	c->err = ret;
#endif
}