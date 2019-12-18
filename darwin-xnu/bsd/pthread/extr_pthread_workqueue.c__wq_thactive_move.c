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
typedef  scalar_t__ wq_thactive_t ;
typedef  int /*<<< orphan*/  thread_qos_t ;
struct workqueue {int /*<<< orphan*/ * wq_thscheduled_count; int /*<<< orphan*/  wq_thactive; } ;

/* Variables and functions */
 size_t _wq_bucket (int /*<<< orphan*/ ) ; 
 scalar_t__ _wq_thactive_offset_for_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_add_orig (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relaxed ; 

__attribute__((used)) static inline void
_wq_thactive_move(struct workqueue *wq,
		thread_qos_t old_qos, thread_qos_t new_qos)
{
	wq_thactive_t v = _wq_thactive_offset_for_qos(new_qos) -
			_wq_thactive_offset_for_qos(old_qos);
	os_atomic_add_orig(&wq->wq_thactive, v, relaxed);
	wq->wq_thscheduled_count[_wq_bucket(old_qos)]--;
	wq->wq_thscheduled_count[_wq_bucket(new_qos)]++;
}