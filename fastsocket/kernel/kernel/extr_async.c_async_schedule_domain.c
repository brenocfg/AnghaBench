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
struct async_domain {int dummy; } ;
typedef  int /*<<< orphan*/  async_func_ptr ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  __async_schedule (int /*<<< orphan*/ *,void*,struct async_domain*) ; 

async_cookie_t async_schedule_domain(async_func_ptr *ptr, void *data,
				     struct async_domain *running)
{
	return __async_schedule(ptr, data, running);
}