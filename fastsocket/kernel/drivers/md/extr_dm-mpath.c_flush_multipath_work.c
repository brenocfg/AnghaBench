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
struct multipath {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmpath_handlerd ; 
 int /*<<< orphan*/  kmultipathd ; 
 int /*<<< orphan*/  multipath_wait_for_pg_init_completion (struct multipath*) ; 

__attribute__((used)) static void flush_multipath_work(struct multipath *m)
{
	flush_workqueue(kmpath_handlerd);
	multipath_wait_for_pg_init_completion(m);
	flush_workqueue(kmultipathd);
	flush_scheduled_work();
}