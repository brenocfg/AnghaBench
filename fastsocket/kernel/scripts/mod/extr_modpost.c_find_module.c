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
struct module {int /*<<< orphan*/  name; struct module* next; } ;

/* Variables and functions */
 struct module* modules ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct module *find_module(char *modname)
{
	struct module *mod;

	for (mod = modules; mod; mod = mod->next)
		if (strcmp(mod->name, modname) == 0)
			break;
	return mod;
}