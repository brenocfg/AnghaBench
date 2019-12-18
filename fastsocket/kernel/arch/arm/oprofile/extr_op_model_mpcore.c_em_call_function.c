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
struct em_function_data {int (* fn ) () ;int ret; } ;

/* Variables and functions */
 int /*<<< orphan*/  em_func (struct em_function_data*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/  (*) (struct em_function_data*),struct em_function_data*,int) ; 

__attribute__((used)) static int em_call_function(int (*fn)(void))
{
	struct em_function_data data;

	data.fn = fn;
	data.ret = 0;

	preempt_disable();
	smp_call_function(em_func, &data, 1);
	em_func(&data);
	preempt_enable();

	return data.ret;
}