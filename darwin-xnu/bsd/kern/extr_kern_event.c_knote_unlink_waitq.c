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
struct waitq {int dummy; } ;
struct kqueue {int /*<<< orphan*/  kq_wqs; } ;
struct knote {int dummy; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  knote_clearstayactive (struct knote*) ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 scalar_t__ waitq_unlink (struct waitq*,int /*<<< orphan*/ *) ; 

int
knote_unlink_waitq(struct knote *kn, struct waitq *wq)
{
	struct kqueue *kq = knote_get_kq(kn);
	kern_return_t kr;

	kr = waitq_unlink(wq, &kq->kq_wqs);
	knote_clearstayactive(kn);
	return ((kr != KERN_SUCCESS) ? EINVAL : 0);
}