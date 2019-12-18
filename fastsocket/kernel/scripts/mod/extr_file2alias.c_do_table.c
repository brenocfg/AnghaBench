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
struct module {char const* name; int /*<<< orphan*/  dev_table_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  device_id_check (char const*,char const*,unsigned long,unsigned long,void*) ; 

__attribute__((used)) static void do_table(void *symval, unsigned long size,
		     unsigned long id_size,
		     const char *device_id,
		     void *function,
		     struct module *mod)
{
	unsigned int i;
	char alias[500];
	int (*do_entry)(const char *, void *entry, char *alias) = function;

	device_id_check(mod->name, device_id, size, id_size, symval);
	/* Leave last one: it's the terminator. */
	size -= id_size;

	for (i = 0; i < size; i += id_size) {
		if (do_entry(mod->name, symval+i, alias)) {
			buf_printf(&mod->dev_table_buf,
				   "MODULE_ALIAS(\"%s\");\n", alias);
		}
	}
}