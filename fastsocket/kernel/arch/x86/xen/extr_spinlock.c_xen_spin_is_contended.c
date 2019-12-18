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
struct xen_spinlock {scalar_t__ spinners; } ;
struct raw_spinlock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int xen_spin_is_contended(struct raw_spinlock *lock)
{
	struct xen_spinlock *xl = (struct xen_spinlock *)lock;

	/* Not strictly true; this is only the count of contended
	   lock-takers entering the slow path. */
	return xl->spinners != 0;
}