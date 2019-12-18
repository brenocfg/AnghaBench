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
struct proc {int dummy; } ;

/* Variables and functions */
 struct workqueue* WQPTR_IS_INITING_VALUE ; 
 struct workqueue* proc_get_wqptr_fast (struct proc*) ; 

__attribute__((used)) static struct workqueue *
proc_get_wqptr(struct proc *p)
{
	struct workqueue *wq = proc_get_wqptr_fast(p);
	return wq == WQPTR_IS_INITING_VALUE ? NULL : wq;
}