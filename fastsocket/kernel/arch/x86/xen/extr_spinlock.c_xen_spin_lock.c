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
struct raw_spinlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xen_spin_lock (struct raw_spinlock*,int) ; 

__attribute__((used)) static void xen_spin_lock(struct raw_spinlock *lock)
{
	__xen_spin_lock(lock, false);
}