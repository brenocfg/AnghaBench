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
struct kqueue {int kq_state; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int KEVENT_FLAG_LEGACY32 ; 
 unsigned int KEVENT_FLAG_LEGACY64 ; 
 int KQ_KEV32 ; 
 int KQ_KEV64 ; 
 int KQ_KEV_QOS ; 
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 int /*<<< orphan*/  kqunlock (struct kqueue*) ; 

__attribute__((used)) static int
kevent_set_kq_mode(struct kqueue *kq, unsigned int flags)
{
	/* each kq should only be used for events of one type */
	kqlock(kq);
	if (kq->kq_state & (KQ_KEV32 | KQ_KEV64 | KQ_KEV_QOS)) {
		if (flags & KEVENT_FLAG_LEGACY32) {
			if ((kq->kq_state & KQ_KEV32) == 0) {
				kqunlock(kq);
				return EINVAL;
			}
		} else if (kq->kq_state & KQ_KEV32) {
			kqunlock(kq);
			return EINVAL;
		}
	} else if (flags & KEVENT_FLAG_LEGACY32) {
		kq->kq_state |= KQ_KEV32;
	} else if (flags & KEVENT_FLAG_LEGACY64) {
		kq->kq_state |= KQ_KEV64;
	} else {
		kq->kq_state |= KQ_KEV_QOS;
	}
	kqunlock(kq);
	return 0;
}