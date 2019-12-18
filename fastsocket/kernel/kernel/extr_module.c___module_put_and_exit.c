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
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_exit (long) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 

void __module_put_and_exit(struct module *mod, long code)
{
	module_put(mod);
	do_exit(code);
}