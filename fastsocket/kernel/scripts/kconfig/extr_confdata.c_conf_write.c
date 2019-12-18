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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {scalar_t__ tri; } ;
struct symbol {int flags; int type; char* name; TYPE_1__ curr; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct menu {struct menu* next; struct menu* parent; struct menu* list; struct symbol* sym; } ;
struct TYPE_4__ {struct menu* list; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SYMBOL_CHOICE ; 
 int SYMBOL_WRITE ; 
#define  S_BOOLEAN 135 
#define  S_HEX 134 
#define  S_INT 133 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
#define  S_STRING 132 
#define  S_TRISTATE 131 
 char* _ (char*) ; 
 int /*<<< orphan*/  conf_get_changed () ; 
 char* conf_get_configname () ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* menu_get_prompt (struct menu*) ; 
 int /*<<< orphan*/  menu_is_visible (struct menu*) ; 
#define  mod 130 
 struct symbol* modules_sym ; 
#define  no 129 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ rename (char*,char*) ; 
 TYPE_2__ rootmenu ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strcspn (char const*,char*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  sym_calc_value (struct symbol*) ; 
 int /*<<< orphan*/  sym_clear_all_valid () ; 
 char* sym_get_string_value (struct symbol*) ; 
 int /*<<< orphan*/  sym_get_tristate_value (struct symbol*) ; 
 struct symbol* sym_lookup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_set_change_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
#define  yes 128 

int conf_write(const char *name)
{
	FILE *out;
	struct symbol *sym;
	struct menu *menu;
	const char *basename;
	char dirname[128], tmpname[128], newname[128];
	int type, l;
	const char *str;
	time_t now;
	int use_timestamp = 1;
	char *env;

	dirname[0] = 0;
	if (name && name[0]) {
		struct stat st;
		char *slash;

		if (!stat(name, &st) && S_ISDIR(st.st_mode)) {
			strcpy(dirname, name);
			strcat(dirname, "/");
			basename = conf_get_configname();
		} else if ((slash = strrchr(name, '/'))) {
			int size = slash - name + 1;
			memcpy(dirname, name, size);
			dirname[size] = 0;
			if (slash[1])
				basename = slash + 1;
			else
				basename = conf_get_configname();
		} else
			basename = name;
	} else
		basename = conf_get_configname();

	sprintf(newname, "%s%s", dirname, basename);
	env = getenv("KCONFIG_OVERWRITECONFIG");
	if (!env || !*env) {
		sprintf(tmpname, "%s.tmpconfig.%d", dirname, (int)getpid());
		out = fopen(tmpname, "w");
	} else {
		*tmpname = 0;
		out = fopen(newname, "w");
	}
	if (!out)
		return 1;

	sym = sym_lookup("KERNELVERSION", 0);
	sym_calc_value(sym);
	time(&now);
	env = getenv("KCONFIG_NOTIMESTAMP");
	if (env && *env)
		use_timestamp = 0;

	fprintf(out, _("#\n"
		       "# Automatically generated make config: don't edit\n"
		       "# Linux kernel version: %s\n"
		       "%s%s"
		       "#\n"),
		     sym_get_string_value(sym),
		     use_timestamp ? "# " : "",
		     use_timestamp ? ctime(&now) : "");

	if (!conf_get_changed())
		sym_clear_all_valid();

	menu = rootmenu.list;
	while (menu) {
		sym = menu->sym;
		if (!sym) {
			if (!menu_is_visible(menu))
				goto next;
			str = menu_get_prompt(menu);
			fprintf(out, "\n"
				     "#\n"
				     "# %s\n"
				     "#\n", str);
		} else if (!(sym->flags & SYMBOL_CHOICE)) {
			sym_calc_value(sym);
			if (!(sym->flags & SYMBOL_WRITE))
				goto next;
			sym->flags &= ~SYMBOL_WRITE;
			type = sym->type;
			if (type == S_TRISTATE) {
				sym_calc_value(modules_sym);
				if (modules_sym->curr.tri == no)
					type = S_BOOLEAN;
			}
			switch (type) {
			case S_BOOLEAN:
			case S_TRISTATE:
				switch (sym_get_tristate_value(sym)) {
				case no:
					fprintf(out, "# CONFIG_%s is not set\n", sym->name);
					break;
				case mod:
					fprintf(out, "CONFIG_%s=m\n", sym->name);
					break;
				case yes:
					fprintf(out, "CONFIG_%s=y\n", sym->name);
					break;
				}
				break;
			case S_STRING:
				str = sym_get_string_value(sym);
				fprintf(out, "CONFIG_%s=\"", sym->name);
				while (1) {
					l = strcspn(str, "\"\\");
					if (l) {
						fwrite(str, l, 1, out);
						str += l;
					}
					if (!*str)
						break;
					fprintf(out, "\\%c", *str++);
				}
				fputs("\"\n", out);
				break;
			case S_HEX:
				str = sym_get_string_value(sym);
				if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X')) {
					fprintf(out, "CONFIG_%s=%s\n", sym->name, str);
					break;
				}
			case S_INT:
				str = sym_get_string_value(sym);
				fprintf(out, "CONFIG_%s=%s\n", sym->name, str);
				break;
			}
		}

	next:
		if (menu->list) {
			menu = menu->list;
			continue;
		}
		if (menu->next)
			menu = menu->next;
		else while ((menu = menu->parent)) {
			if (menu->next) {
				menu = menu->next;
				break;
			}
		}
	}
	fclose(out);

	if (*tmpname) {
		strcat(dirname, basename);
		strcat(dirname, ".old");
		rename(newname, dirname);
		if (rename(tmpname, newname))
			return 1;
	}

	printf(_("#\n"
		 "# configuration written to %s\n"
		 "#\n"), newname);

	sym_set_change_count(0);

	return 0;
}