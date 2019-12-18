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
struct i2o_exec_wait {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct i2o_exec_wait* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i2o_exec_wait *i2o_exec_wait_alloc(void)
{
	struct i2o_exec_wait *wait;

	wait = kzalloc(sizeof(*wait), GFP_KERNEL);
	if (!wait)
		return NULL;

	INIT_LIST_HEAD(&wait->list);
	spin_lock_init(&wait->lock);

	return wait;
}