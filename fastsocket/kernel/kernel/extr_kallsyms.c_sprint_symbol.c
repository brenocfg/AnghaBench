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
 char* kallsyms_lookup (unsigned long,unsigned long*,unsigned long*,char**,char*) ; 
 int sprintf (char*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char*) ; 

int sprint_symbol(char *buffer, unsigned long address)
{
	char *modname;
	const char *name;
	unsigned long offset, size;
	int len;

	name = kallsyms_lookup(address, &size, &offset, &modname, buffer);
	if (!name)
		return sprintf(buffer, "0x%lx", address);

	if (name != buffer)
		strcpy(buffer, name);
	len = strlen(buffer);
	buffer += len;

	if (modname)
		len += sprintf(buffer, "+%#lx/%#lx [%s]",
						offset, size, modname);
	else
		len += sprintf(buffer, "+%#lx/%#lx", offset, size);

	return len;
}