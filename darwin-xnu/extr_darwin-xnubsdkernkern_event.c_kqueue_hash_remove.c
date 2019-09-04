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
struct proc {struct filedesc* p_fd; } ;
struct kqworkloop {int /*<<< orphan*/  kqwl_dynamicid; } ;
struct kqueue {int kq_state; } ;
struct kqlist {int dummy; } ;
struct filedesc {int /*<<< orphan*/  fd_kqhashmask; struct kqlist* fd_kqhash; } ;

/* Variables and functions */
 int KQ_DYNAMIC ; 
 size_t KQ_HASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KQ_WORKLOOP ; 
 int /*<<< orphan*/  SLIST_REMOVE (struct kqlist*,struct kqworkloop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kqhash_lock_held (struct proc*) ; 
 int /*<<< orphan*/  kqwl_hashlink ; 
 int /*<<< orphan*/  kqworkloop ; 

__attribute__((used)) static void
kqueue_hash_remove(
	struct proc *p,
	struct kqueue *kq)
{
	struct kqworkloop *kqwl = (struct kqworkloop *)kq;
	struct filedesc *fdp = p->p_fd;
	struct kqlist *list;

	/* should hold the kq hash lock */
	kqhash_lock_held(p);

	if ((kq->kq_state & KQ_DYNAMIC) == 0) {
		assert(kq->kq_state & KQ_DYNAMIC);
		return;
	}
	assert(kq->kq_state & KQ_WORKLOOP); /* for now */
	list = &fdp->fd_kqhash[KQ_HASH(kqwl->kqwl_dynamicid, fdp->fd_kqhashmask)];
	SLIST_REMOVE(list, kqwl, kqworkloop, kqwl_hashlink);
}