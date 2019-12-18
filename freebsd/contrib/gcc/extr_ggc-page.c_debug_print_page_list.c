#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int context_depth; int num_free_objects; struct TYPE_3__* next; } ;
typedef  TYPE_1__ page_entry ;
struct TYPE_4__ {TYPE_1__** pages; scalar_t__* page_tails; } ;

/* Variables and functions */
 TYPE_2__ G ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

void
debug_print_page_list (int order)
{
  page_entry *p;
  printf ("Head=%p, Tail=%p:\n", (void *) G.pages[order],
	  (void *) G.page_tails[order]);
  p = G.pages[order];
  while (p != NULL)
    {
      printf ("%p(%1d|%3d) -> ", (void *) p, p->context_depth,
	      p->num_free_objects);
      p = p->next;
    }
  printf ("NULL\n");
  fflush (stdout);
}