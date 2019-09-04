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
typedef  int /*<<< orphan*/  thread_qos_t ;
struct kqueue {int dummy; } ;
struct knote {int kn_status; } ;

/* Variables and functions */
 int KN_ACTIVE ; 
 int /*<<< orphan*/  knote_apply_qos_override (struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knote_dequeue (struct knote*) ; 
 scalar_t__ knote_enqueue (struct knote*) ; 
 scalar_t__ knote_should_apply_qos_override (struct kqueue*,struct knote*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knote_wakeup (struct knote*) ; 

__attribute__((used)) static void
knote_adjust_qos(struct kqueue *kq, struct knote *kn, int result)
{
	thread_qos_t qos;
	if (knote_should_apply_qos_override(kq, kn, result, &qos)) {
		knote_dequeue(kn);
		knote_apply_qos_override(kn, qos);
		if (knote_enqueue(kn) && (kn->kn_status & KN_ACTIVE)) {
			knote_wakeup(kn);
		}
	}
}