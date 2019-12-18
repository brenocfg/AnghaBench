#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wildcard_spec {scalar_t__ sorted; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;
struct wildcard_list {struct wildcard_list* next; TYPE_1__ spec; } ;
struct TYPE_6__ {int filenames_sorted; int /*<<< orphan*/  children; int /*<<< orphan*/  keep_sections; struct wildcard_list* section_list; int /*<<< orphan*/ * filename; } ;
typedef  TYPE_2__ lang_wild_statement_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  analyze_walk_wild_section_handler (TYPE_2__*) ; 
 scalar_t__ by_name ; 
 void* lang_has_input_file ; 
 int /*<<< orphan*/  lang_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_wild_statement ; 
 TYPE_2__* new_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* placed_commons ; 
 int /*<<< orphan*/  stat_ptr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wildcardp (int /*<<< orphan*/ *) ; 

void
lang_add_wild (struct wildcard_spec *filespec,
	       struct wildcard_list *section_list,
	       bfd_boolean keep_sections)
{
  struct wildcard_list *curr, *next;
  lang_wild_statement_type *new;

  /* Reverse the list as the parser puts it back to front.  */
  for (curr = section_list, section_list = NULL;
       curr != NULL;
       section_list = curr, curr = next)
    {
      if (curr->spec.name != NULL && strcmp (curr->spec.name, "COMMON") == 0)
	placed_commons = TRUE;

      next = curr->next;
      curr->next = section_list;
    }

  if (filespec != NULL && filespec->name != NULL)
    {
      if (strcmp (filespec->name, "*") == 0)
	filespec->name = NULL;
      else if (! wildcardp (filespec->name))
	lang_has_input_file = TRUE;
    }

  new = new_stat (lang_wild_statement, stat_ptr);
  new->filename = NULL;
  new->filenames_sorted = FALSE;
  if (filespec != NULL)
    {
      new->filename = filespec->name;
      new->filenames_sorted = filespec->sorted == by_name;
    }
  new->section_list = section_list;
  new->keep_sections = keep_sections;
  lang_list_init (&new->children);
  analyze_walk_wild_section_handler (new);
}