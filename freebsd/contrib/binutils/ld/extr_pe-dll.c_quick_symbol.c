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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {char* name; int flags; int value; int /*<<< orphan*/ * section; } ;
typedef  TYPE_1__ asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 TYPE_1__* bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  symptr ; 
 TYPE_1__** symtab ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
quick_symbol (bfd *abfd,
	      const char *n1,
	      const char *n2,
	      const char *n3,
	      asection *sec,
	      int flags,
	      int addr)
{
  asymbol *sym;
  char *name = xmalloc (strlen (n1) + strlen (n2) + strlen (n3) + 1);

  strcpy (name, n1);
  strcat (name, n2);
  strcat (name, n3);
  sym = bfd_make_empty_symbol (abfd);
  sym->name = name;
  sym->section = sec;
  sym->flags = flags;
  sym->value = addr;
  symtab[symptr++] = sym;
}