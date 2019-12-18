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
 int stub1 () ; 

__attribute__((used)) static void em_func(void *data)
{
	struct em_function_data *d = data;
	int ret = d->fn();
	if (ret)
		d->ret = ret;
}