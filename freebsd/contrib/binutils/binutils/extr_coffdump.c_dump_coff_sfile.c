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
struct coff_sfile {char* name; struct coff_sfile* next; int /*<<< orphan*/  scope; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_coff_scope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  tab (int) ; 

__attribute__((used)) static void
dump_coff_sfile (struct coff_sfile *p)
{
  tab (1);
  printf ("List of source files");
  nl ();

  while (p)
    {
      tab (0);
      printf ("Source file %s", p->name);
      nl ();
      dump_coff_scope (p->scope);
      p = p->next;
    }
  tab (-1);
}