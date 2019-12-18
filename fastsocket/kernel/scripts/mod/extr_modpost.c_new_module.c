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
struct module {char* name; int gpl_compatible; struct module* next; } ;

/* Variables and functions */
 void* NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (struct module*,int /*<<< orphan*/ ,int) ; 
 struct module* modules ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static struct module *new_module(char *modname)
{
	struct module *mod;
	char *p, *s;

	mod = NOFAIL(malloc(sizeof(*mod)));
	memset(mod, 0, sizeof(*mod));
	p = NOFAIL(strdup(modname));

	/* strip trailing .o */
	s = strrchr(p, '.');
	if (s != NULL)
		if (strcmp(s, ".o") == 0)
			*s = '\0';

	/* add to list */
	mod->name = p;
	mod->gpl_compatible = -1;
	mod->next = modules;
	modules = mod;

	return mod;
}