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
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {struct kqrequest* uu_kqr_bound; } ;
struct kqueue {int dummy; } ;
struct kqrequest {int dummy; } ;

/* Variables and functions */
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ kqr_kqworkloop (struct kqrequest*) ; 

__attribute__((used)) static struct kqueue *
kevent_get_bound_kqworkloop(thread_t thread)
{
	struct uthread *ut = get_bsdthread_info(thread);
	struct kqrequest *kqr = ut->uu_kqr_bound;

	return kqr ? (struct kqueue *)kqr_kqworkloop(kqr) : NULL;
}