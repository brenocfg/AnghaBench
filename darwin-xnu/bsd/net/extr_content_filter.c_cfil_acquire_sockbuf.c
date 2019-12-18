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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/ * thread_t ;
struct sockbuf {int sb_flags; scalar_t__ sb_wantlock; scalar_t__ sb_cfil_refs; int /*<<< orphan*/ * sb_cfil_thread; } ;
struct socket {TYPE_2__* so_proto; struct sockbuf so_rcv; struct sockbuf so_snd; } ;
struct cfil_info {int cfi_flags; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
struct TYPE_4__ {TYPE_1__* pr_domain; int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 int CFIF_DROP ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int EPIPE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PR_F_WILLUNLOCK ; 
 int /*<<< orphan*/  PSOCK ; 
 int SB_LOCK ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfil_acquire_sockbuf(struct socket *so, struct cfil_info *cfil_info, int outgoing)
{
	thread_t tp = current_thread();
	struct sockbuf *sb = outgoing ? &so->so_snd : &so->so_rcv;
	lck_mtx_t *mutex_held;
	int error = 0;

	/*
	 * Wait until no thread is holding the sockbuf and other content
	 * filter threads have released the sockbuf
	 */
	while ((sb->sb_flags & SB_LOCK) ||
		(sb->sb_cfil_thread != NULL && sb->sb_cfil_thread != tp)) {
		if (so->so_proto->pr_getlock != NULL)
			mutex_held = (*so->so_proto->pr_getlock)(so, PR_F_WILLUNLOCK);
		else
			mutex_held = so->so_proto->pr_domain->dom_mtx;

		LCK_MTX_ASSERT(mutex_held, LCK_MTX_ASSERT_OWNED);

		sb->sb_wantlock++;
		VERIFY(sb->sb_wantlock != 0);

		msleep(&sb->sb_flags, mutex_held, PSOCK, "cfil_acquire_sockbuf",
			NULL);

		VERIFY(sb->sb_wantlock != 0);
		sb->sb_wantlock--;
	}
	/*
	 * Use reference count for repetitive calls on same thread
	 */
	if (sb->sb_cfil_refs == 0) {
		VERIFY(sb->sb_cfil_thread == NULL);
		VERIFY((sb->sb_flags & SB_LOCK) == 0);

		sb->sb_cfil_thread = tp;
		sb->sb_flags |= SB_LOCK;
	}
	sb->sb_cfil_refs++;

	/* We acquire the socket buffer when we need to cleanup */
	if (cfil_info == NULL) {
		CFIL_LOG(LOG_ERR, "so %llx cfil detached",
			(uint64_t)VM_KERNEL_ADDRPERM(so));
		error = 0;
	} else if (cfil_info->cfi_flags & CFIF_DROP) {
		CFIL_LOG(LOG_ERR, "so %llx drop set",
			(uint64_t)VM_KERNEL_ADDRPERM(so));
		error = EPIPE;
	}

	return (error);
}