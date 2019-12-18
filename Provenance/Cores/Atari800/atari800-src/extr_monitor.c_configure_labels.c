#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int addr; } ;
typedef  TYPE_1__ symtable_rec ;
typedef  int UWORD ;
struct TYPE_5__ {int addr; char* name; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  Util_strupper (char*) ; 
 int /*<<< orphan*/  add_user_label (char const*,int) ; 
 TYPE_1__* find_user_label (char const*) ; 
 int /*<<< orphan*/  free_user_labels () ; 
 scalar_t__ get_hex (int*) ; 
 void* get_token () ; 
 int /*<<< orphan*/  load_user_labels (void*) ; 
 scalar_t__ pager () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ symtable_builtin_enable ; 
 TYPE_2__* symtable_user ; 
 int symtable_user_size ; 

__attribute__((used)) static void configure_labels(UWORD *addr)
{
	char *cmd = get_token();
	if (cmd == NULL) {
		printf("Built-in labels are %sabled.\n", symtable_builtin_enable ? "en" : "dis");
		if (symtable_user_size > 0)
			printf("Using %d user-defined label%s.\n",
				symtable_user_size, (symtable_user_size > 1) ? "s" : "");
		else
			printf("There are no user-defined labels.\n");
		printf(
			"Labels are displayed in disassembly listings.\n"
			"You may also use them as command arguments"
#ifdef MONITOR_ASSEMBLER
				" and in the built-in assembler"
#endif
				".\n"
			"Usage:\n"
			"LABELS OFF            - no labels\n"
			"LABELS BUILTIN        - use only built-in labels\n"
			"LABELS LOAD filename  - use only labels loaded from file\n"
			"LABELS ADD filename   - use built-in and loaded labels\n"
			"LABELS SET name value - define a label\n"
			"LABELS LIST           - list user-defined labels\n"
		);
	}
	else {
		Util_strupper(cmd);
		if (strcmp(cmd, "OFF") == 0) {
			symtable_builtin_enable = FALSE;
			free_user_labels();
		}
		else if (strcmp(cmd, "BUILTIN") == 0) {
			symtable_builtin_enable = TRUE;
			free_user_labels();
		}
		else if (strcmp(cmd, "LOAD") == 0) {
			symtable_builtin_enable = FALSE;
			load_user_labels(get_token());
		}
		else if (strcmp(cmd, "ADD") == 0) {
			symtable_builtin_enable = TRUE;
			load_user_labels(get_token());
		}
		else if (strcmp(cmd, "SET") == 0) {
			const char *name = get_token();
			if (name != NULL && get_hex(addr)) {
				symtable_rec *p = find_user_label(name);
				if (p != NULL) {
					if (p->addr != *addr) {
						printf("%s redefined (previous value: %04X)\n", name, p->addr);
						p->addr = *addr;
					}
				}
				else
					add_user_label(name, *addr);
			}
			else
				printf("Missing or bad arguments\n");
		}
		else if (strcmp(cmd, "LIST") == 0) {
			int i;
			int nlines = 0;
			for (i = 0; i < symtable_user_size; i++) {
				if (++nlines == 24) {
					if (pager())
						break;
					nlines = 0;
				}
				printf("%04X %s\n", symtable_user[i].addr, symtable_user[i].name);
			}
		}
		else
			printf("Invalid command, type \"LABELS\" for help\n");
	}
}