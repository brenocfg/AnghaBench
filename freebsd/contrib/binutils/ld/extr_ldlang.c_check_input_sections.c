#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* head; } ;
struct TYPE_11__ {TYPE_1__ children; } ;
struct TYPE_12__ {int type; TYPE_4__* next; } ;
struct TYPE_13__ {TYPE_2__ group_statement; int /*<<< orphan*/  wild_statement; TYPE_3__ header; } ;
typedef  TYPE_4__ lang_statement_union_type ;
struct TYPE_14__ {int /*<<< orphan*/  all_input_readonly; } ;
typedef  TYPE_5__ lang_output_section_statement_type ;
struct TYPE_15__ {TYPE_4__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_section_callback ; 
 TYPE_7__ constructor_list ; 
#define  lang_constructors_statement_enum 130 
#define  lang_group_statement_enum 129 
#define  lang_wild_statement_enum 128 
 int /*<<< orphan*/  walk_wild (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void
check_input_sections
  (lang_statement_union_type *s,
   lang_output_section_statement_type *output_section_statement)
{
  for (; s != (lang_statement_union_type *) NULL; s = s->header.next)
    {
      switch (s->header.type)
      {
      case lang_wild_statement_enum:
	walk_wild (&s->wild_statement, check_section_callback,
		   output_section_statement);
	if (! output_section_statement->all_input_readonly)
	  return;
	break;
      case lang_constructors_statement_enum:
	check_input_sections (constructor_list.head,
			      output_section_statement);
	if (! output_section_statement->all_input_readonly)
	  return;
	break;
      case lang_group_statement_enum:
	check_input_sections (s->group_statement.children.head,
			      output_section_statement);
	if (! output_section_statement->all_input_readonly)
	  return;
	break;
      default:
	break;
      }
    }
}