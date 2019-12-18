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
struct property {int length; struct property* value; struct property* name; struct property* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct property*) ; 
 void* kmalloc (int const,int /*<<< orphan*/ ) ; 
 struct property* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct property*,unsigned char const*,int const) ; 
 int /*<<< orphan*/  strcpy (struct property*,char const*) ; 
 int const strlen (char const*) ; 

__attribute__((used)) static struct property *new_property(const char *name, const int length,
				     const unsigned char *value, struct property *last)
{
	struct property *new = kzalloc(sizeof(*new), GFP_KERNEL);

	if (!new)
		return NULL;

	if (!(new->name = kmalloc(strlen(name) + 1, GFP_KERNEL)))
		goto cleanup;
	if (!(new->value = kmalloc(length + 1, GFP_KERNEL)))
		goto cleanup;

	strcpy(new->name, name);
	memcpy(new->value, value, length);
	*(((char *)new->value) + length) = 0;
	new->length = length;
	new->next = last;
	return new;

cleanup:
	kfree(new->name);
	kfree(new->value);
	kfree(new);
	return NULL;
}