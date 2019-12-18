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
struct macro {int length; int perm; struct macro* value; struct macro* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct macro*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct macro*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  macros ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  strcpy (struct macro*,char const*) ; 
 int strlen (char const*) ; 

int
define_macro(const char *name, const char *value)
{
	struct macro *m;

	if ((m = malloc(sizeof(*m))) == NULL)
		return (-1);
	if ((m->name = malloc(strlen(name) + 1)) == NULL) {
		free(m);
		return (-1);
	}
	strcpy(m->name, name);
	if ((m->value = malloc(strlen(value) + 1)) == NULL) {
		free(m->name);
		free(m);
		return (-1);
	}
	strcpy(m->value, value);
	m->length = strlen(value);
	m->perm = 1;
	LIST_INSERT_HEAD(&macros, m, link);
	return (0);
}