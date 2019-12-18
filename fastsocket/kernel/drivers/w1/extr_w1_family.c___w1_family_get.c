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
struct w1_family {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic_inc () ; 
 int /*<<< orphan*/  smp_mb__before_atomic_inc () ; 

void __w1_family_get(struct w1_family *f)
{
	smp_mb__before_atomic_inc();
	atomic_inc(&f->refcnt);
	smp_mb__after_atomic_inc();
}