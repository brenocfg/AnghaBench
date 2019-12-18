#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* head; } ;
struct TYPE_13__ {TYPE_4__ children; } ;
struct TYPE_10__ {TYPE_6__* head; } ;
struct TYPE_11__ {TYPE_2__ children; } ;
struct TYPE_9__ {int type; TYPE_6__* next; } ;
struct TYPE_14__ {TYPE_5__ group_statement; TYPE_3__ output_section_statement; int /*<<< orphan*/  wild_statement; TYPE_1__ header; } ;
typedef  TYPE_6__ lang_statement_union_type ;
struct TYPE_15__ {TYPE_6__* head; } ;

/* Variables and functions */
 TYPE_8__ constructor_list ; 
 int /*<<< orphan*/  gc_section_callback ; 
#define  lang_constructors_statement_enum 131 
#define  lang_group_statement_enum 130 
#define  lang_output_section_statement_enum 129 
#define  lang_wild_statement_enum 128 
 int /*<<< orphan*/  walk_wild (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lang_gc_sections_1 (lang_statement_union_type *s)
{
  for (; s != NULL; s = s->header.next)
    {
      switch (s->header.type)
	{
	case lang_wild_statement_enum:
	  walk_wild (&s->wild_statement, gc_section_callback, NULL);
	  break;
	case lang_constructors_statement_enum:
	  lang_gc_sections_1 (constructor_list.head);
	  break;
	case lang_output_section_statement_enum:
	  lang_gc_sections_1 (s->output_section_statement.children.head);
	  break;
	case lang_group_statement_enum:
	  lang_gc_sections_1 (s->group_statement.children.head);
	  break;
	default:
	  break;
	}
    }
}