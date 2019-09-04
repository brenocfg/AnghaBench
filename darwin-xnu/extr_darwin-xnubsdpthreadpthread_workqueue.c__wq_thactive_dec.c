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
typedef  int /*<<< orphan*/  wq_thactive_t ;
typedef  int /*<<< orphan*/  thread_qos_t ;
struct workqueue {int /*<<< orphan*/  wq_thactive; } ;

/* Variables and functions */
 int /*<<< orphan*/  _wq_thactive_offset_for_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_sub_orig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relaxed ; 

__attribute__((used)) static inline wq_thactive_t
_wq_thactive_dec(struct workqueue *wq, thread_qos_t qos)
{
	wq_thactive_t v = _wq_thactive_offset_for_qos(qos);
	return os_atomic_sub_orig(&wq->wq_thactive, v, relaxed);
}