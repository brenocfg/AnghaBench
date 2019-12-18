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
struct block_lock {struct task_struct** holders; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int MAX_HOLDERS ; 

__attribute__((used)) static unsigned __find_holder(struct block_lock *lock,
			      struct task_struct *task)
{
	unsigned i;

	for (i = 0; i < MAX_HOLDERS; i++)
		if (lock->holders[i] == task)
			break;

	BUG_ON(i == MAX_HOLDERS);
	return i;
}