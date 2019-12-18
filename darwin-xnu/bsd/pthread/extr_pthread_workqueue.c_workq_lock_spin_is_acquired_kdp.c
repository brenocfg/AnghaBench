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
 int kdp_lck_spin_is_acquired (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
workq_lock_spin_is_acquired_kdp(struct workqueue *wq)
{
	return kdp_lck_spin_is_acquired(&wq->wq_lock);
}