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
 scalar_t__ _wq_exiting (struct workqueue*) ; 
 struct workqueue* proc_get_wqptr (struct proc*) ; 

bool
workq_is_exiting(struct proc *p)
{
	struct workqueue *wq = proc_get_wqptr(p);
	return !wq || _wq_exiting(wq);
}