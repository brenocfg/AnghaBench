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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CountLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  outline ; 
 char* symbol_prefix ; 

__attribute__((used)) static void
define_prefixed(FILE * fp, const char *name)
{
    int bump_line = CountLine(fp);
    if (bump_line)
	++outline;
    fprintf(fp, "\n");

    if (bump_line)
	++outline;
    fprintf(fp, "#ifndef %s\n", name);

    if (bump_line)
	++outline;
    fprintf(fp, "#define %-10s %s%s\n", name, symbol_prefix, name + 2);

    if (bump_line)
	++outline;
    fprintf(fp, "#endif /* %s */\n", name);
}