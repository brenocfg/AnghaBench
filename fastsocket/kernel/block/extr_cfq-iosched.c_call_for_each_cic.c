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
struct io_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __call_for_each_cic (struct io_context*,void (*) (struct io_context*,struct cfq_io_context*)) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void
call_for_each_cic(struct io_context *ioc,
		  void (*func)(struct io_context *, struct cfq_io_context *))
{
	rcu_read_lock();
	__call_for_each_cic(ioc, func);
	rcu_read_unlock();
}