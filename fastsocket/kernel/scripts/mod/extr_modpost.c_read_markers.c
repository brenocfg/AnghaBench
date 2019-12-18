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
struct module {int skip; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_marker (struct module*,char*,char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 struct module* find_module (char*) ; 
 char* get_next_line (unsigned long*,void*,unsigned long) ; 
 void* grab_file (char const*,unsigned long*) ; 
 int have_vmlinux ; 
 scalar_t__ is_vmlinux (char*) ; 
 struct module* new_module (char*) ; 
 int /*<<< orphan*/  release_file (void*,unsigned long) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void read_markers(const char *fname)
{
	unsigned long size, pos = 0;
	void *file = grab_file(fname, &size);
	char *line;

	if (!file)		/* No old markers, silently ignore */
		return;

	while ((line = get_next_line(&pos, file, size))) {
		char *marker, *modname, *fmt;
		struct module *mod;

		marker = line;
		modname = strchr(marker, '\t');
		if (!modname)
			goto fail;
		*modname++ = '\0';
		fmt = strchr(modname, '\t');
		if (!fmt)
			goto fail;
		*fmt++ = '\0';
		if (*marker == '\0' || *modname == '\0')
			goto fail;

		mod = find_module(modname);
		if (!mod) {
			mod = new_module(modname);
			mod->skip = 1;
		}
		if (is_vmlinux(modname)) {
			have_vmlinux = 1;
			mod->skip = 0;
		}

		if (!mod->skip)
			add_marker(mod, marker, fmt);
	}
	release_file(file, size);
	return;
fail:
	fatal("parse error in markers list file\n");
}