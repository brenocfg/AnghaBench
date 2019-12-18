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
struct module {char** markers; int nmarkers; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char** NOFAIL (char*) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 char* realloc (char**,int) ; 

__attribute__((used)) static void add_marker(struct module *mod, const char *name, const char *fmt)
{
	char *line = NULL;
	asprintf(&line, "%s\t%s\t%s\n", name, mod->name, fmt);
	NOFAIL(line);

	mod->markers = NOFAIL(realloc(mod->markers, ((mod->nmarkers + 1) *
						     sizeof mod->markers[0])));
	mod->markers[mod->nmarkers++] = line;
}