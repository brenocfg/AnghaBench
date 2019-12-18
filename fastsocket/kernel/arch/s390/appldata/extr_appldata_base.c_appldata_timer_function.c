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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  appldata_expire_count ; 
 int /*<<< orphan*/  appldata_wq ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 

__attribute__((used)) static void appldata_timer_function(unsigned long data)
{
	if (atomic_dec_and_test(&appldata_expire_count)) {
		atomic_set(&appldata_expire_count, num_online_cpus());
		queue_work(appldata_wq, (struct work_struct *) data);
	}
}