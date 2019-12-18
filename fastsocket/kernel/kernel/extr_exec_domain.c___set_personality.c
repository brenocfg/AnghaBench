#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct exec_domain {int /*<<< orphan*/  module; } ;
struct TYPE_4__ {unsigned int personality; } ;
struct TYPE_3__ {struct exec_domain* exec_domain; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 TYPE_1__* current_thread_info () ; 
 struct exec_domain* lookup_exec_domain (unsigned int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

int
__set_personality(unsigned int personality)
{
	struct exec_domain	*ep, *oep;

	ep = lookup_exec_domain(personality);
	if (ep == current_thread_info()->exec_domain) {
		current->personality = personality;
		module_put(ep->module);
		return 0;
	}

	current->personality = personality;
	oep = current_thread_info()->exec_domain;
	current_thread_info()->exec_domain = ep;

	module_put(oep->module);
	return 0;
}