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
struct remote_function_call {int (* func ) (void*) ;void* info; int ret; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  remote_function ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,struct remote_function_call*,int) ; 

__attribute__((used)) static int cpu_function_call(int cpu, int (*func) (void *info), void *info)
{
	struct remote_function_call data = {
		.p	= NULL,
		.func	= func,
		.info	= info,
		.ret	= -ENXIO, /* No such CPU */
	};

	smp_call_function_single(cpu, remote_function, &data, 1);

	return data.ret;
}