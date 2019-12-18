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

/* Variables and functions */
 int /*<<< orphan*/  cfile ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char,char const*) ; 

__attribute__((used)) static void
add(const char *p, const char *type)
{
	for (; *p; ++p) {
		char c = *p;
		switch (c) {
		case '\t': c = 't';  break;
		case '\n': c = 'n';  break;
		case '\'': c = '\''; break;
		case '\\': c = '\\'; break;

		default:
			fprintf(cfile, "\t[SYNBASE + '%c'] = %s,\n", c, type);
			continue;
		}
		fprintf(cfile, "\t[SYNBASE + '\\%c'] = %s,\n", c, type);
	}
}