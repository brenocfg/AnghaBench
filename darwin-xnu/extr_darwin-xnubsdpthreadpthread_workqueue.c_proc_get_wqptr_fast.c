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
struct workqueue {int dummy; } ;
struct proc {int /*<<< orphan*/  p_wqptr; } ;

/* Variables and functions */
 struct workqueue* os_atomic_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relaxed ; 

__attribute__((used)) static struct workqueue *
proc_get_wqptr_fast(struct proc *p)
{
	return os_atomic_load(&p->p_wqptr, relaxed);
}