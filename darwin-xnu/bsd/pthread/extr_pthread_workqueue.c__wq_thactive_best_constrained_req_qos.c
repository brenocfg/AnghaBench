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
 int /*<<< orphan*/  WQ_THACTIVE_BEST_CONSTRAINED_REQ_QOS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline thread_qos_t
_wq_thactive_best_constrained_req_qos(struct workqueue *wq)
{
	// Avoid expensive atomic operations: the three bits we're loading are in
	// a single byte, and always updated under the workqueue lock
	wq_thactive_t v = *(wq_thactive_t *)&wq->wq_thactive;
	return WQ_THACTIVE_BEST_CONSTRAINED_REQ_QOS(v);
}