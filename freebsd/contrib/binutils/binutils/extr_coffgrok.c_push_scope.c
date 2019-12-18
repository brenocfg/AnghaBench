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
struct coff_scope {struct coff_scope* parent; struct coff_scope* list_tail; struct coff_scope* list_head; struct coff_scope* next; } ;

/* Variables and functions */
 struct coff_scope* empty_scope () ; 
 struct coff_scope* top_scope ; 

__attribute__((used)) static void
push_scope (int link)
{
  struct coff_scope *n = empty_scope ();
  if (link)
    {
      if (top_scope)
	{
	  if (top_scope->list_tail)
	    {
	      top_scope->list_tail->next = n;
	    }
	  else
	    {
	      top_scope->list_head = n;
	    }
	  top_scope->list_tail = n;
	}
    }
  n->parent = top_scope;

  top_scope = n;
}