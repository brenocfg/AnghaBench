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
struct salinfo_data {int /*<<< orphan*/  cpu_event; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_saved_lock ; 
 int /*<<< orphan*/  salinfo_work_to_do (struct salinfo_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
salinfo_timeout_check(struct salinfo_data *data)
{
	unsigned long flags;
	if (!data->open)
		return;
	if (!cpus_empty(data->cpu_event)) {
		spin_lock_irqsave(&data_saved_lock, flags);
		salinfo_work_to_do(data);
		spin_unlock_irqrestore(&data_saved_lock, flags);
	}
}