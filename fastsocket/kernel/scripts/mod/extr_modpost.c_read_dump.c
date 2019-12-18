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
struct symbol {unsigned int kernel; int preloaded; } ;
struct module {int skip; } ;

/* Variables and functions */
 int /*<<< orphan*/  export_no (char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 struct module* find_module (char*) ; 
 char* get_next_line (unsigned long*,void*,unsigned long) ; 
 void* grab_file (char const*,unsigned long*) ; 
 int have_vmlinux ; 
 scalar_t__ is_vmlinux (char*) ; 
 struct module* new_module (char*) ; 
 char* strchr (char*,char) ; 
 unsigned int strtoul (char*,char**,int) ; 
 struct symbol* sym_add_exported (char*,struct module*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_update_crc (char*,struct module*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_dump(const char *fname, unsigned int kernel)
{
	unsigned long size, pos = 0;
	void *file = grab_file(fname, &size);
	char *line;

	if (!file)
		/* No symbol versions, silently ignore */
		return;

	while ((line = get_next_line(&pos, file, size))) {
		char *symname, *modname, *d, *export, *end;
		unsigned int crc;
		struct module *mod;
		struct symbol *s;

		if (!(symname = strchr(line, '\t')))
			goto fail;
		*symname++ = '\0';
		if (!(modname = strchr(symname, '\t')))
			goto fail;
		*modname++ = '\0';
		if ((export = strchr(modname, '\t')) != NULL)
			*export++ = '\0';
		if (export && ((end = strchr(export, '\t')) != NULL))
			*end = '\0';
		crc = strtoul(line, &d, 16);
		if (*symname == '\0' || *modname == '\0' || *d != '\0')
			goto fail;
		mod = find_module(modname);
		if (!mod) {
			if (is_vmlinux(modname))
				have_vmlinux = 1;
			mod = new_module(modname);
			mod->skip = 1;
		}
		s = sym_add_exported(symname, mod, export_no(export));
		s->kernel    = kernel;
		s->preloaded = 1;
		sym_update_crc(symname, mod, crc, export_no(export));
	}
	return;
fail:
	fatal("parse error in symbol dump file\n");
}