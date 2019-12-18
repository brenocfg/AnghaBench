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
struct task_struct {TYPE_1__* signal; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait_chldexit; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __wake_up_sync_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct task_struct*) ; 

void __wake_up_parent(struct task_struct *p, struct task_struct *parent)
{
	__wake_up_sync_key(&parent->signal->wait_chldexit,
				TASK_INTERRUPTIBLE, 1, p);
}