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
struct kqrequest {int kqr_state; scalar_t__ kqr_thread; } ;
struct kqworkloop {struct kqrequest kqwl_request; } ;

/* Variables and functions */
 int KQR_THREQUESTED ; 
 scalar_t__ THREAD_NULL ; 

__attribute__((used)) static inline bool
filt_wlturnstile_interlock_is_workq(struct kqworkloop *kqwl)
{
	struct kqrequest *kqr = &kqwl->kqwl_request;
	return (kqr->kqr_state & KQR_THREQUESTED) &&
			(kqr->kqr_thread == THREAD_NULL);
}