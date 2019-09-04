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
typedef  int uint32_t ;
struct kqueue_info {int dummy; } ;
struct kqueue_dyninfo {int /*<<< orphan*/  kqdi_info; } ;
struct kqueue {int dummy; } ;
typedef  int /*<<< orphan*/ * proc_t ;
typedef  int /*<<< orphan*/  kqueue_id_t ;
typedef  int int32_t ;

/* Variables and functions */
 int ENOBUFS ; 
 int ESRCH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int copyout (struct kqueue_dyninfo*,int /*<<< orphan*/ ,int) ; 
 int fill_kqueue_dyninfo (struct kqueue*,struct kqueue_dyninfo*) ; 
 int fill_kqueueinfo (struct kqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqhash_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqhash_unlock (int /*<<< orphan*/ *) ; 
 struct kqueue* kqueue_hash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqueue_release_last (int /*<<< orphan*/ *,struct kqueue*) ; 
 int /*<<< orphan*/  kqueue_retain (struct kqueue*) ; 

int
kevent_copyout_dynkqinfo(void *proc, kqueue_id_t kq_id, user_addr_t ubuf,
		uint32_t ubufsize, int32_t *size_out)
{
	proc_t p = (proc_t)proc;
	struct kqueue *kq;
	int err = 0;
	struct kqueue_dyninfo kqdi = { };

	assert(p != NULL);

	if (ubufsize < sizeof(struct kqueue_info)) {
		return ENOBUFS;
	}

	kqhash_lock(p);
	kq = kqueue_hash_lookup(p, kq_id);
	if (!kq) {
		kqhash_unlock(p);
		return ESRCH;
	}
	kqueue_retain(kq);
	kqhash_unlock(p);

	/*
	 * backward compatibility: allow the argument to this call to only be
	 * a struct kqueue_info
	 */
	if (ubufsize >= sizeof(struct kqueue_dyninfo)) {
		ubufsize = sizeof(struct kqueue_dyninfo);
		err = fill_kqueue_dyninfo(kq, &kqdi);
	} else {
		ubufsize = sizeof(struct kqueue_info);
		err = fill_kqueueinfo(kq, &kqdi.kqdi_info);
	}
	if (err == 0 && (err = copyout(&kqdi, ubuf, ubufsize)) == 0) {
		*size_out = ubufsize;
	}
	kqueue_release_last(p, kq);
	return err;
}