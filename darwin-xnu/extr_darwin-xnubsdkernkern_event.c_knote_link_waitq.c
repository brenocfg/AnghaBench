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
typedef  int /*<<< orphan*/  uint64_t ;
struct waitq {int dummy; } ;
struct kqueue {int /*<<< orphan*/  kq_wqs; } ;
struct knote {int dummy; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  WAITQ_ALREADY_LOCKED ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  knote_markstayactive (struct knote*) ; 
 scalar_t__ waitq_link (struct waitq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
knote_link_waitq(struct knote *kn, struct waitq *wq, uint64_t *reserved_link)
{
	struct kqueue *kq = knote_get_kq(kn);
	kern_return_t kr;

	kr = waitq_link(wq, &kq->kq_wqs, WAITQ_ALREADY_LOCKED, reserved_link);
	if (kr == KERN_SUCCESS) {
		knote_markstayactive(kn);
		return (0);
	} else {
		return (EINVAL);
	}
}