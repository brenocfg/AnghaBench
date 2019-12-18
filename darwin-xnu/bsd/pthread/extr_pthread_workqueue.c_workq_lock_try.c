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
struct workqueue {int /*<<< orphan*/  wq_lock; } ;

/* Variables and functions */
 int lck_spin_try_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
workq_lock_try(struct workqueue *wq)
{
	return lck_spin_try_lock(&wq->wq_lock);
}