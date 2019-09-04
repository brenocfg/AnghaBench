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
struct TYPE_3__ {int /*<<< orphan*/  trp_value; } ;
typedef  TYPE_1__ workq_threadreq_param_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct proc {struct filedesc* p_fd; } ;
struct kqworkloop {int /*<<< orphan*/  kqwl_params; scalar_t__ kqwl_dynamicid; } ;
struct kqueue {int kq_state; } ;
struct fileproc {int dummy; } ;
struct filedesc {struct kqueue* fd_wqkqueue; } ;
typedef  scalar_t__ kqueue_id_t ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 unsigned int KEVENT_FLAG_DYNAMIC_KQUEUE ; 
 unsigned int KEVENT_FLAG_DYNAMIC_KQ_MUST_EXIST ; 
 unsigned int KEVENT_FLAG_DYNAMIC_KQ_MUST_NOT_EXIST ; 
 unsigned int KEVENT_FLAG_KERNEL ; 
 unsigned int KEVENT_FLAG_WORKLOOP ; 
 unsigned int KEVENT_FLAG_WORKQ ; 
 int /*<<< orphan*/  KQUEUE_MIGHT_BE_LAST_REF ; 
 int KQ_DYNAMIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_getfkq (struct proc*,int,struct fileproc**,struct kqueue**) ; 
 int /*<<< orphan*/  is_workqueue_thread (int /*<<< orphan*/ ) ; 
 struct kqueue* kevent_get_bound_kqworkloop (int /*<<< orphan*/ ) ; 
 int kevent_set_kq_mode (struct kqueue*,unsigned int) ; 
 int /*<<< orphan*/  knhash_lock (struct proc*) ; 
 int /*<<< orphan*/  knhash_unlock (struct proc*) ; 
 int /*<<< orphan*/  kqhash_lock (struct proc*) ; 
 int /*<<< orphan*/  kqhash_unlock (struct proc*) ; 
 struct kqueue* kqueue_alloc (struct proc*,unsigned int) ; 
 int /*<<< orphan*/  kqueue_dealloc (struct kqueue*) ; 
 int /*<<< orphan*/  kqueue_hash_init_if_needed (struct proc*) ; 
 int /*<<< orphan*/  kqueue_hash_insert (struct proc*,scalar_t__,struct kqueue*) ; 
 struct kqueue* kqueue_hash_lookup (struct proc*,scalar_t__) ; 
 int /*<<< orphan*/  kqueue_release (struct kqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqueue_retain (struct kqueue*) ; 

__attribute__((used)) static int
kevent_get_kq(struct proc *p, kqueue_id_t id, workq_threadreq_param_t *trp,
		unsigned int flags, struct fileproc **fpp, int *fdp,
		struct kqueue **kqp)
{
	struct filedesc *descp = p->p_fd;
	struct fileproc *fp = NULL;
	struct kqueue *kq = NULL;
	int fd = 0;
	int error = 0;
	thread_t th = current_thread();

	assert(!trp || (flags & KEVENT_FLAG_WORKLOOP));

	/* Was the workloop flag passed?  Then it is for sure only a workloop */
	if (flags & KEVENT_FLAG_DYNAMIC_KQUEUE) {
		assert(flags & KEVENT_FLAG_WORKLOOP);
		assert(!trp || (flags & KEVENT_FLAG_DYNAMIC_KQ_MUST_NOT_EXIST));
		kq = kevent_get_bound_kqworkloop(th);

		/*
		 * when kevent_id_internal is called from within the
		 * kernel, and the passed 'id' value is '-1' then we
		 * look for the currently bound workloop kq.
		 */
		if (id == (kqueue_id_t)-1 &&
		    (flags & KEVENT_FLAG_KERNEL) &&
		    (flags & KEVENT_FLAG_WORKLOOP)) {

			if (!is_workqueue_thread(th) || !kq) {
				return EINVAL;
			}

			kqueue_retain(kq);
			goto out;
		}

		if (id == 0 || id == (kqueue_id_t)-1) {
			return EINVAL;
		}

		/* try shortcut on kq lookup for bound threads */
		if (kq != NULL && ((struct kqworkloop *)kq)->kqwl_dynamicid == id) {

			if (flags & KEVENT_FLAG_DYNAMIC_KQ_MUST_NOT_EXIST) {
				return EEXIST;
			}

			/* retain a reference while working with this kq. */
			assert(kq->kq_state & KQ_DYNAMIC);
			kqueue_retain(kq);
			goto out;
		}

		/* look for the kq on the hash table */
		kqhash_lock(p);
		kq = kqueue_hash_lookup(p, id);
		if (kq == NULL) {
			kqhash_unlock(p);

			if (flags & KEVENT_FLAG_DYNAMIC_KQ_MUST_EXIST) {
				return ENOENT;
			}

			struct kqueue *alloc_kq;
			alloc_kq = kqueue_alloc(p, flags);
			if (!alloc_kq) {
				return ENOMEM;
			}

			kqhash_lock(p);
			kqueue_hash_init_if_needed(p);
			kq = kqueue_hash_lookup(p, id);
			if (kq == NULL) {
				/* insert our new one */
				kq = alloc_kq;
				if (trp) {
					struct kqworkloop *kqwl = (struct kqworkloop *)kq;
					kqwl->kqwl_params = trp->trp_value;
				}
				kqueue_hash_insert(p, id, kq);
				kqhash_unlock(p);
			} else if (flags & KEVENT_FLAG_DYNAMIC_KQ_MUST_NOT_EXIST) {
				/* lost race and caller wants an error */
				kqhash_unlock(p);
				kqueue_release(alloc_kq, KQUEUE_MIGHT_BE_LAST_REF);
				kqueue_dealloc(alloc_kq);
				return EEXIST;
			} else {
				/* lost race, retain existing workloop */
				kqueue_retain(kq);
				kqhash_unlock(p);
				kqueue_release(alloc_kq, KQUEUE_MIGHT_BE_LAST_REF);
				kqueue_dealloc(alloc_kq);
			}
		} else {

			if (flags & KEVENT_FLAG_DYNAMIC_KQ_MUST_NOT_EXIST) {
				kqhash_unlock(p);
				return  EEXIST;
			}

			/* retain a reference while working with this kq. */
			assert(kq->kq_state & KQ_DYNAMIC);
			kqueue_retain(kq);
			kqhash_unlock(p);
		}

	} else if (flags & KEVENT_FLAG_WORKQ) {
		/* must already exist for bound threads. */
		if (flags & KEVENT_FLAG_KERNEL) {
			assert(descp->fd_wqkqueue != NULL);
		}

		/*
		 * use the private kq associated with the proc workq.
		 * Just being a thread within the process (and not
		 * being the exit/exec thread) is enough to hold a
		 * reference on this special kq.
		 */
		kq = descp->fd_wqkqueue;
		if (kq == NULL) {
			struct kqueue *alloc_kq = kqueue_alloc(p, KEVENT_FLAG_WORKQ);
			if (alloc_kq == NULL) {
				return ENOMEM;
			}

			knhash_lock(p);
			if (descp->fd_wqkqueue == NULL) {
				kq = descp->fd_wqkqueue = alloc_kq;
				knhash_unlock(p);
			} else {
				knhash_unlock(p);
				kq = descp->fd_wqkqueue;
				kqueue_dealloc(alloc_kq);
			}
		}
	} else {
		/* get a usecount for the kq itself */
		fd = (int)id;
		if ((error = fp_getfkq(p, fd, &fp, &kq)) != 0)
			return (error);
	}
	if ((error = kevent_set_kq_mode(kq, flags)) != 0) {
		/* drop the usecount */
		if (fp != NULL)
			fp_drop(p, fd, fp, 0);
		return error;
	}

out:
	*fpp = fp;
	*fdp = fd;
	*kqp = kq;

	return error;
}