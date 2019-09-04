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
struct kqrequest {int kqr_state; int /*<<< orphan*/  kqr_thread; } ;
struct kqworkloop {struct kqrequest kqwl_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_KEVENT_RETURN_TO_KERNEL ; 
 int KQR_R2K_NOTIF_ARMED ; 
 int /*<<< orphan*/  act_set_astkevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kq_req_held (struct kqworkloop*) ; 

__attribute__((used)) static inline void
kqworkloop_request_fire_r2k_notification(struct kqworkloop *kqwl)
{
	struct kqrequest *kqr = &kqwl->kqwl_request;

	kq_req_held(kqwl);

	if (kqr->kqr_state & KQR_R2K_NOTIF_ARMED) {
		assert(kqr->kqr_thread);
		kqr->kqr_state &= ~KQR_R2K_NOTIF_ARMED;
		act_set_astkevent(kqr->kqr_thread, AST_KEVENT_RETURN_TO_KERNEL);
	}
}