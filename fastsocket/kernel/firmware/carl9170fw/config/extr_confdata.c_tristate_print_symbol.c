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
struct symbol {scalar_t__ type; int name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CONFIG_ ; 
 scalar_t__ S_TRISTATE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int,char) ; 
 scalar_t__ toupper (char const) ; 

__attribute__((used)) static void
tristate_print_symbol(FILE *fp, struct symbol *sym, const char *value, void *arg)
{

	if (sym->type == S_TRISTATE && *value != 'n')
		fprintf(fp, "%s%s=%c\n", CONFIG_, sym->name, (char)toupper(*value));
}