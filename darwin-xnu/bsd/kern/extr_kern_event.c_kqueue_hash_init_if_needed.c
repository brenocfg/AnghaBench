#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct kqlist {int dummy; } ;
struct filedesc {int /*<<< orphan*/  fd_kqhashmask; struct kqlist* fd_kqhash; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_6__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_KQ_HASHSIZE ; 
 int /*<<< orphan*/  FREE (struct kqlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_KQUEUE ; 
 scalar_t__ __improbable (int /*<<< orphan*/ ) ; 
 struct kqlist* hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqhash_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  kqhash_lock_held (TYPE_1__*) ; 
 int /*<<< orphan*/  kqhash_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
kqueue_hash_init_if_needed(proc_t p)
{
	struct filedesc *fdp = p->p_fd;

	kqhash_lock_held(p);

	if (__improbable(fdp->fd_kqhash == NULL)) {
		struct kqlist *alloc_hash;
		u_long alloc_mask;

		kqhash_unlock(p);
		alloc_hash = hashinit(CONFIG_KQ_HASHSIZE, M_KQUEUE, &alloc_mask);
		kqhash_lock(p);

		/* See if we won the race */
		if (fdp->fd_kqhashmask == 0) {
			fdp->fd_kqhash = alloc_hash;
			fdp->fd_kqhashmask = alloc_mask;
		} else {
			kqhash_unlock(p);
			FREE(alloc_hash, M_KQUEUE);
			kqhash_lock(p);
		}
	}
}