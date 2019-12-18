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
typedef  int /*<<< orphan*/  on_exit_func_t ;

/* Variables and functions */
 size_t ATEXIT_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __handle_on_exit_funcs ; 
 void** __on_exit_args ; 
 size_t __on_exit_count ; 
 int /*<<< orphan*/ * __on_exit_funcs ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_exit(on_exit_func_t function, void *arg)
{
	if (__on_exit_count == ATEXIT_MAX)
		return -ENOMEM;
	else if (__on_exit_count == 0)
		atexit(__handle_on_exit_funcs);
	__on_exit_funcs[__on_exit_count] = function;
	__on_exit_args[__on_exit_count++] = arg;
	return 0;
}