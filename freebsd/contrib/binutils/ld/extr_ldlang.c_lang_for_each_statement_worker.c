#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_8__* head; } ;
struct TYPE_14__ {TYPE_1__ children; } ;
struct TYPE_18__ {TYPE_8__* head; } ;
struct TYPE_19__ {TYPE_6__ children; } ;
struct TYPE_16__ {TYPE_8__* head; } ;
struct TYPE_17__ {TYPE_4__ children; } ;
struct TYPE_15__ {int type; TYPE_8__* next; } ;
struct TYPE_20__ {TYPE_2__ group_statement; TYPE_7__ wild_statement; TYPE_5__ output_section_statement; TYPE_3__ header; } ;
typedef  TYPE_8__ lang_statement_union_type ;
struct TYPE_12__ {TYPE_8__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL () ; 
 TYPE_11__ constructor_list ; 
#define  lang_address_statement_enum 142 
#define  lang_assignment_statement_enum 141 
#define  lang_constructors_statement_enum 140 
#define  lang_data_statement_enum 139 
#define  lang_fill_statement_enum 138 
#define  lang_group_statement_enum 137 
#define  lang_input_section_enum 136 
#define  lang_input_statement_enum 135 
#define  lang_object_symbols_statement_enum 134 
#define  lang_output_section_statement_enum 133 
#define  lang_output_statement_enum 132 
#define  lang_padding_statement_enum 131 
#define  lang_reloc_statement_enum 130 
#define  lang_target_statement_enum 129 
#define  lang_wild_statement_enum 128 

__attribute__((used)) static void
lang_for_each_statement_worker (void (*func) (lang_statement_union_type *),
				lang_statement_union_type *s)
{
  for (; s != NULL; s = s->header.next)
    {
      func (s);

      switch (s->header.type)
	{
	case lang_constructors_statement_enum:
	  lang_for_each_statement_worker (func, constructor_list.head);
	  break;
	case lang_output_section_statement_enum:
	  lang_for_each_statement_worker
	    (func, s->output_section_statement.children.head);
	  break;
	case lang_wild_statement_enum:
	  lang_for_each_statement_worker (func,
					  s->wild_statement.children.head);
	  break;
	case lang_group_statement_enum:
	  lang_for_each_statement_worker (func,
					  s->group_statement.children.head);
	  break;
	case lang_data_statement_enum:
	case lang_reloc_statement_enum:
	case lang_object_symbols_statement_enum:
	case lang_output_statement_enum:
	case lang_target_statement_enum:
	case lang_input_section_enum:
	case lang_input_statement_enum:
	case lang_assignment_statement_enum:
	case lang_padding_statement_enum:
	case lang_address_statement_enum:
	case lang_fill_statement_enum:
	  break;
	default:
	  FAIL ();
	  break;
	}
    }
}