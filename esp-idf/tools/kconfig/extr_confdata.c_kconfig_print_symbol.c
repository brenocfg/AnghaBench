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
struct symbol {int type; char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CONFIG_ ; 
#define  S_BOOLEAN 129 
#define  S_TRISTATE 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char const*) ; 

__attribute__((used)) static void
kconfig_print_symbol(FILE *fp, struct symbol *sym, const char *value, void *arg)
{

	switch (sym->type) {
	case S_BOOLEAN:
	case S_TRISTATE:
		break;
	default:
		break;
	}

	fprintf(fp, "%s%s=%s\n", CONFIG_, sym->name, value);
}