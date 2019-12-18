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
 int HZ ; 
 int /*<<< orphan*/  bios_check_work ; 
 int /*<<< orphan*/  check_for_bios_corruption () ; 
 int corruption_check_period ; 
 int /*<<< orphan*/  round_jiffies_relative (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_corruption(struct work_struct *dummy)
{
	check_for_bios_corruption();
	schedule_delayed_work(&bios_check_work,
		round_jiffies_relative(corruption_check_period*HZ)); 
}