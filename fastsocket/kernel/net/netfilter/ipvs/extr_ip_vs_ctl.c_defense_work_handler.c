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
 int /*<<< orphan*/  DEFENSE_TIMER_PERIOD ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  defense_work ; 
 int /*<<< orphan*/  ip_vs_dropentry ; 
 int /*<<< orphan*/  ip_vs_random_dropentry () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_defense_level () ; 

__attribute__((used)) static void defense_work_handler(struct work_struct *work)
{
	update_defense_level();
	if (atomic_read(&ip_vs_dropentry))
		ip_vs_random_dropentry();

	schedule_delayed_work(&defense_work, DEFENSE_TIMER_PERIOD);
}