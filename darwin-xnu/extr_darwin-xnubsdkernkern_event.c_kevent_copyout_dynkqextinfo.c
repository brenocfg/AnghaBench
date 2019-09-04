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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kqueue {int dummy; } ;
typedef  int /*<<< orphan*/ * proc_t ;
typedef  int /*<<< orphan*/  kqueue_id_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqhash_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqhash_unlock (int /*<<< orphan*/ *) ; 
 struct kqueue* kqueue_hash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqueue_release_last (int /*<<< orphan*/ *,struct kqueue*) ; 
 int /*<<< orphan*/  kqueue_retain (struct kqueue*) ; 
 int pid_kqueue_extinfo (int /*<<< orphan*/ *,struct kqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
kevent_copyout_dynkqextinfo(void *proc, kqueue_id_t kq_id, user_addr_t ubuf,
		uint32_t ubufsize, int32_t *nknotes_out)
{
	proc_t p = (proc_t)proc;
	struct kqueue *kq;
	int err;

	assert(p != NULL);

	kqhash_lock(p);
	kq = kqueue_hash_lookup(p, kq_id);
	if (!kq) {
		kqhash_unlock(p);
		return ESRCH;
	}
	kqueue_retain(kq);
	kqhash_unlock(p);

	err = pid_kqueue_extinfo(p, kq, ubuf, ubufsize, nknotes_out);
	kqueue_release_last(p, kq);
	return err;
}