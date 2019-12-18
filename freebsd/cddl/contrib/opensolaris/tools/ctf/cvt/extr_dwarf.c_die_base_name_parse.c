#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int intr_signed; char intr_iformat; int /*<<< orphan*/  intr_type; } ;
typedef  TYPE_1__ intr_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_INT ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  terminate (char*,char const*) ; 
 TYPE_1__* xcalloc (int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static intr_t *
die_base_name_parse(const char *name, char **newp)
{
	char buf[256];
	char const *base;
	char *c;
	int nlong = 0, nshort = 0, nchar = 0, nint = 0;
	int sign = 1;
	char fmt = '\0';
	intr_t *intr;

	if (strlen(name) > sizeof (buf) - 1)
		terminate("base type name \"%s\" is too long\n", name);

	strncpy(buf, name, sizeof (buf));

	for (c = strtok(buf, " "); c != NULL; c = strtok(NULL, " ")) {
		if (strcmp(c, "signed") == 0)
			sign = 1;
		else if (strcmp(c, "unsigned") == 0)
			sign = 0;
		else if (strcmp(c, "long") == 0)
			nlong++;
		else if (strcmp(c, "char") == 0) {
			nchar++;
			fmt = 'c';
		} else if (strcmp(c, "short") == 0)
			nshort++;
		else if (strcmp(c, "int") == 0)
			nint++;
		else {
			/*
			 * If we don't recognize any of the tokens, we'll tell
			 * the caller to fall back to the dwarf-provided
			 * encoding information.
			 */
			return (NULL);
		}
	}

	if (nchar > 1 || nshort > 1 || nint > 1 || nlong > 2)
		return (NULL);

	if (nchar > 0) {
		if (nlong > 0 || nshort > 0 || nint > 0)
			return (NULL);

		base = "char";

	} else if (nshort > 0) {
		if (nlong > 0)
			return (NULL);

		base = "short";

	} else if (nlong > 0) {
		base = "long";

	} else {
		base = "int";
	}

	intr = xcalloc(sizeof (intr_t));
	intr->intr_type = INTR_INT;
	intr->intr_signed = sign;
	intr->intr_iformat = fmt;

	snprintf(buf, sizeof (buf), "%s%s%s",
	    (sign ? "" : "unsigned "),
	    (nlong > 1 ? "long " : ""),
	    base);

	*newp = xstrdup(buf);
	return (intr);
}