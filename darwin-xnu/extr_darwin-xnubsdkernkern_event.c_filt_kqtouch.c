#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kqueue {int /*<<< orphan*/  kq_count; } ;
struct knote {int /*<<< orphan*/  kn_data; TYPE_1__* kn_fp; } ;
struct kevent_internal_s {int dummy; } ;
struct TYPE_2__ {scalar_t__ f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 int /*<<< orphan*/  kqunlock (struct kqueue*) ; 

__attribute__((used)) static int
filt_kqtouch(struct knote *kn, struct kevent_internal_s *kev)
{
#pragma unused(kev)
	struct kqueue *kq = (struct kqueue *)kn->kn_fp->f_data;
	int res;

	kqlock(kq);
	kn->kn_data = kq->kq_count;
	res = (kn->kn_data > 0);

	kqunlock(kq);

	return res;
}