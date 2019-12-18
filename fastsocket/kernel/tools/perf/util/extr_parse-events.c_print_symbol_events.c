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
struct event_symbol {char* symbol; char* alias; } ;

/* Variables and functions */
 int MAX_NAME_LEN ; 
 char** event_type_descriptors ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strglobmatch (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void print_symbol_events(const char *event_glob, unsigned type,
				struct event_symbol *syms, unsigned max,
				bool name_only)
{
	unsigned i, printed = 0;
	char name[MAX_NAME_LEN];

	for (i = 0; i < max; i++, syms++) {

		if (event_glob != NULL && 
		    !(strglobmatch(syms->symbol, event_glob) ||
		      (syms->alias && strglobmatch(syms->alias, event_glob))))
			continue;

		if (name_only) {
			printf("%s ", syms->symbol);
			continue;
		}

		if (strlen(syms->alias))
			snprintf(name, MAX_NAME_LEN, "%s OR %s", syms->symbol, syms->alias);
		else
			strncpy(name, syms->symbol, MAX_NAME_LEN);

		printf("  %-50s [%s]\n", name, event_type_descriptors[type]);

		printed++;
	}

	if (printed)
		printf("\n");
}