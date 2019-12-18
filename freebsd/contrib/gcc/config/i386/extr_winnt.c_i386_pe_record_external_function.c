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
typedef  int /*<<< orphan*/  tree ;
struct extern_list {char const* name; int /*<<< orphan*/  decl; struct extern_list* next; } ;

/* Variables and functions */
 struct extern_list* extern_head ; 
 scalar_t__ ggc_alloc (int) ; 

void
i386_pe_record_external_function (tree decl, const char *name)
{
  struct extern_list *p;

  p = (struct extern_list *) ggc_alloc (sizeof *p);
  p->next = extern_head;
  p->decl = decl;
  p->name = name;
  extern_head = p;
}