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
struct workqueue {int /*<<< orphan*/  wq_refcnt; } ;

/* Variables and functions */
 scalar_t__ os_ref_release_relaxed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  workq_destroy (struct workqueue*) ; 

__attribute__((used)) static void
workq_deallocate(struct workqueue *wq)
{
	if (os_ref_release_relaxed(&wq->wq_refcnt) == 0) {
		workq_destroy(wq);
	}
}