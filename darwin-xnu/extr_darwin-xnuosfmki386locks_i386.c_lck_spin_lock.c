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
typedef  int /*<<< orphan*/  usimple_lock_t ;
typedef  int /*<<< orphan*/  lck_spin_t ;

/* Variables and functions */
 int /*<<< orphan*/  usimple_lock (int /*<<< orphan*/ ) ; 

void
lck_spin_lock(
	lck_spin_t	*lck)
{
	usimple_lock((usimple_lock_t) lck);
}