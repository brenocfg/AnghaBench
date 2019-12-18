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
struct property {char* name; char* value; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct property* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static struct property *new_property(const char *name, int length,
		const void *value)
{
	struct property *np = kzalloc(sizeof(*np) + strlen(name) + 1 + length,
			GFP_KERNEL);

	if (!np)
		return NULL;
	np->name = (char *)(np + 1);
	np->value = np->name + strlen(name) + 1;
	strcpy(np->name, name);
	memcpy(np->value, value, length);
	np->length = length;
	return np;
}