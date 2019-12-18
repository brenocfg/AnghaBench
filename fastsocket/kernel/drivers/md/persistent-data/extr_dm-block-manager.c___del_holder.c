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
struct task_struct {int dummy; } ;
struct block_lock {int /*<<< orphan*/ ** holders; } ;

/* Variables and functions */
 unsigned int __find_holder (struct block_lock*,struct task_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static void __del_holder(struct block_lock *lock, struct task_struct *task)
{
	unsigned h = __find_holder(lock, task);
	lock->holders[h] = NULL;
	put_task_struct(task);
}