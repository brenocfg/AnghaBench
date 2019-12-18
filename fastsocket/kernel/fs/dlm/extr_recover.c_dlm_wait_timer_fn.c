#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dlm_ls {int /*<<< orphan*/  ls_wait_general; int /*<<< orphan*/  ls_timer; } ;
struct TYPE_2__ {int ci_recover_timer; } ;

/* Variables and functions */
 int HZ ; 
 TYPE_1__ dlm_config ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_wait_timer_fn(unsigned long data)
{
	struct dlm_ls *ls = (struct dlm_ls *) data;
	mod_timer(&ls->ls_timer, jiffies + (dlm_config.ci_recover_timer * HZ));
	wake_up(&ls->ls_wait_general);
}