#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {TYPE_1__* module; struct symbol* next; } ;
struct module {struct symbol* unres; int /*<<< orphan*/  name; int /*<<< orphan*/  seen; struct module* next; } ;
struct buffer {int dummy; } ;
struct TYPE_2__ {int seen; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 
 int /*<<< orphan*/  is_vmlinux (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void add_depends(struct buffer *b, struct module *mod,
			struct module *modules)
{
	struct symbol *s;
	struct module *m;
	int first = 1;

	for (m = modules; m; m = m->next)
		m->seen = is_vmlinux(m->name);

	buf_printf(b, "\n");
	buf_printf(b, "static const char __module_depends[]\n");
	buf_printf(b, "__used\n");
	buf_printf(b, "__attribute__((section(\".modinfo\"))) =\n");
	buf_printf(b, "\"depends=");
	for (s = mod->unres; s; s = s->next) {
		const char *p;
		if (!s->module)
			continue;

		if (s->module->seen)
			continue;

		s->module->seen = 1;
		p = strrchr(s->module->name, '/');
		if (p)
			p++;
		else
			p = s->module->name;
		buf_printf(b, "%s%s", first ? "" : ",", p);
		first = 0;
	}
	buf_printf(b, "\";\n");
}