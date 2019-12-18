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
struct bfd_elf_version_expr {struct bfd_elf_version_expr* next; } ;
struct TYPE_3__ {struct bfd_elf_version_expr* list; } ;
struct bfd_elf_dynamic_list {int /*<<< orphan*/  match; TYPE_1__ head; } ;
struct TYPE_4__ {struct bfd_elf_dynamic_list* dynamic_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  lang_vers_match ; 
 TYPE_2__ link_info ; 
 struct bfd_elf_dynamic_list* xcalloc (int,int) ; 

void
lang_append_dynamic_list (struct bfd_elf_version_expr *dynamic)
{
  if (link_info.dynamic_list)
    {
      struct bfd_elf_version_expr *tail;
      for (tail = dynamic; tail->next != NULL; tail = tail->next)
	;
      tail->next = link_info.dynamic_list->head.list;
      link_info.dynamic_list->head.list = dynamic;
    }
  else
    {
      struct bfd_elf_dynamic_list *d;

      d = xcalloc (1, sizeof *d);
      d->head.list = dynamic;
      d->match = lang_vers_match;
      link_info.dynamic_list = d;
    }
}