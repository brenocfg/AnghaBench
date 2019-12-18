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
struct coff_symbol {char* name; int tag; int number; struct coff_symbol* next; int /*<<< orphan*/  visible; int /*<<< orphan*/  where; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_coff_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_coff_visible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_coff_where (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  tab (int) ; 

__attribute__((used)) static void
dump_coff_symbol (struct coff_symbol *p)
{
  tab (1);
  printf ("List of symbols");
  nl ();

  while (p)
    {
      tab (1);
      tab (1);
      printf ("Symbol  %s, tag %d, number %d", p->name, p->tag, p->number);
      nl ();
      tab (-1);
      tab (1);
      printf ("Type");
      nl ();
      dump_coff_type (p->type);
      tab (-1);
      tab (1);
      printf ("Where");
      dump_coff_where (p->where);
      tab (-1);
      tab (1);
      printf ("Visible");
      dump_coff_visible (p->visible);
      tab (-1);
      p = p->next;
      tab (-1);
    }
  tab (-1);
}