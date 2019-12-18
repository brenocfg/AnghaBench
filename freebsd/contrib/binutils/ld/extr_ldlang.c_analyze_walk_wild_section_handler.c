#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
struct wildcard_list {TYPE_1__ spec; struct wildcard_list* next; } ;
struct TYPE_5__ {struct wildcard_list** handler_data; struct wildcard_list* section_list; int /*<<< orphan*/  walk_wild_section_handler; int /*<<< orphan*/ * tree; } ;
typedef  TYPE_2__ lang_wild_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/  is_simple_wild (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_wild_section_general ; 
 int /*<<< orphan*/  walk_wild_section_specs1_wild0 ; 
 int /*<<< orphan*/  walk_wild_section_specs1_wild1 ; 
 int /*<<< orphan*/  walk_wild_section_specs2_wild1 ; 
 int /*<<< orphan*/  walk_wild_section_specs3_wild2 ; 
 int /*<<< orphan*/  walk_wild_section_specs4_wild2 ; 
 scalar_t__ wild_spec_can_overlap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wildcardp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
analyze_walk_wild_section_handler (lang_wild_statement_type *ptr)
{
  int sec_count = 0;
  int wild_name_count = 0;
  struct wildcard_list *sec;
  int signature;
  int data_counter;

  ptr->walk_wild_section_handler = walk_wild_section_general;
  ptr->handler_data[0] = NULL;
  ptr->handler_data[1] = NULL;
  ptr->handler_data[2] = NULL;
  ptr->handler_data[3] = NULL;
  ptr->tree = NULL;

  /* Count how many wildcard_specs there are, and how many of those
     actually use wildcards in the name.  Also, bail out if any of the
     wildcard names are NULL. (Can this actually happen?
     walk_wild_section used to test for it.)  And bail out if any
     of the wildcards are more complex than a simple string
     ending in a single '*'.  */
  for (sec = ptr->section_list; sec != NULL; sec = sec->next)
    {
      ++sec_count;
      if (sec->spec.name == NULL)
	return;
      if (wildcardp (sec->spec.name))
	{
	  ++wild_name_count;
	  if (!is_simple_wild (sec->spec.name))
	    return;
	}
    }

  /* The zero-spec case would be easy to optimize but it doesn't
     happen in practice.  Likewise, more than 4 specs doesn't
     happen in practice.  */
  if (sec_count == 0 || sec_count > 4)
    return;

  /* Check that no two specs can match the same section.  */
  for (sec = ptr->section_list; sec != NULL; sec = sec->next)
    {
      struct wildcard_list *sec2;
      for (sec2 = sec->next; sec2 != NULL; sec2 = sec2->next)
	{
	  if (wild_spec_can_overlap (sec->spec.name, sec2->spec.name))
	    return;
	}
    }

  signature = (sec_count << 8) + wild_name_count;
  switch (signature)
    {
    case 0x0100:
      ptr->walk_wild_section_handler = walk_wild_section_specs1_wild0;
      break;
    case 0x0101:
      ptr->walk_wild_section_handler = walk_wild_section_specs1_wild1;
      break;
    case 0x0201:
      ptr->walk_wild_section_handler = walk_wild_section_specs2_wild1;
      break;
    case 0x0302:
      ptr->walk_wild_section_handler = walk_wild_section_specs3_wild2;
      break;
    case 0x0402:
      ptr->walk_wild_section_handler = walk_wild_section_specs4_wild2;
      break;
    default:
      return;
    }

  /* Now fill the data array with pointers to the specs, first the
     specs with non-wildcard names, then the specs with wildcard
     names.  It's OK to process the specs in different order from the
     given order, because we've already determined that no section
     will match more than one spec.  */
  data_counter = 0;
  for (sec = ptr->section_list; sec != NULL; sec = sec->next)
    if (!wildcardp (sec->spec.name))
      ptr->handler_data[data_counter++] = sec;
  for (sec = ptr->section_list; sec != NULL; sec = sec->next)
    if (wildcardp (sec->spec.name))
      ptr->handler_data[data_counter++] = sec;
}