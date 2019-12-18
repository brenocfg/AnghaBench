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
struct symbol {unsigned int weak; struct symbol* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct symbol* NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct symbol*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct symbol *alloc_symbol(const char *name, unsigned int weak,
				   struct symbol *next)
{
	struct symbol *s = NOFAIL(malloc(sizeof(*s) + strlen(name) + 1));

	memset(s, 0, sizeof(*s));
	strcpy(s->name, name);
	s->weak = weak;
	s->next = next;
	return s;
}