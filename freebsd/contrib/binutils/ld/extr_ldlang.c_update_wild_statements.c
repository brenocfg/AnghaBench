#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int sorted; } ;
struct wildcard_list {TYPE_3__ spec; struct wildcard_list* next; } ;
struct TYPE_17__ {TYPE_8__* head; } ;
struct TYPE_18__ {TYPE_6__ children; } ;
struct TYPE_15__ {TYPE_8__* head; } ;
struct TYPE_16__ {TYPE_4__ children; } ;
struct TYPE_13__ {struct wildcard_list* section_list; } ;
struct TYPE_12__ {int /*<<< orphan*/  type; TYPE_8__* next; } ;
struct TYPE_19__ {TYPE_7__ group_statement; TYPE_5__ output_section_statement; TYPE_2__ wild_statement; TYPE_1__ header; } ;
typedef  TYPE_8__ lang_statement_union_type ;
struct TYPE_11__ {TYPE_8__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL () ; 
#define  by_alignment 134 
 int by_alignment_name ; 
#define  by_name 133 
 int by_name_alignment ; 
 TYPE_10__ constructor_list ; 
#define  lang_constructors_statement_enum 132 
#define  lang_group_statement_enum 131 
#define  lang_output_section_statement_enum 130 
#define  lang_wild_statement_enum 129 
#define  none 128 
 int sort_section ; 

__attribute__((used)) static void
update_wild_statements (lang_statement_union_type *s)
{
  struct wildcard_list *sec;

  switch (sort_section)
    {
    default:
      FAIL ();

    case none:
      break;

    case by_name:
    case by_alignment:
      for (; s != NULL; s = s->header.next)
	{
	  switch (s->header.type)
	    {
	    default:
	      break;

	    case lang_wild_statement_enum:
	      sec = s->wild_statement.section_list;
	      for (sec = s->wild_statement.section_list; sec != NULL;
		   sec = sec->next)
		{
		  switch (sec->spec.sorted)
		    {
		    case none:
		      sec->spec.sorted = sort_section;
		      break;
		    case by_name:
		      if (sort_section == by_alignment)
			sec->spec.sorted = by_name_alignment;
		      break;
		    case by_alignment:
		      if (sort_section == by_name)
			sec->spec.sorted = by_alignment_name;
		      break;
		    default:
		      break;
		    }
		}
	      break;

	    case lang_constructors_statement_enum:
	      update_wild_statements (constructor_list.head);
	      break;

	    case lang_output_section_statement_enum:
	      update_wild_statements
		(s->output_section_statement.children.head);
	      break;

	    case lang_group_statement_enum:
	      update_wild_statements (s->group_statement.children.head);
	      break;
	    }
	}
      break;
    }
}