#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_18__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  address; int /*<<< orphan*/  section_name; TYPE_8__* segment; } ;
struct TYPE_31__ {int /*<<< orphan*/  exp; } ;
struct TYPE_30__ {int /*<<< orphan*/  exp; } ;
struct TYPE_28__ {TYPE_11__* head; } ;
struct TYPE_29__ {TYPE_4__ children; } ;
struct TYPE_27__ {char* target; } ;
struct TYPE_26__ {TYPE_11__* head; } ;
struct TYPE_23__ {int constraint; int flags; int /*<<< orphan*/  addr_tree; TYPE_9__* bfd_section; TYPE_2__ children; int /*<<< orphan*/  all_input_readonly; } ;
struct TYPE_25__ {int type; TYPE_11__* next; } ;
struct TYPE_22__ {TYPE_10__ address_statement; TYPE_7__ assignment_statement; TYPE_6__ data_statement; TYPE_5__ group_statement; TYPE_3__ target_statement; TYPE_12__ output_section_statement; int /*<<< orphan*/  wild_statement; TYPE_1__ header; } ;
typedef  TYPE_11__ lang_statement_union_type ;
typedef  TYPE_12__ lang_output_section_statement_type ;
typedef  int flagword ;
struct TYPE_33__ {int flags; } ;
struct TYPE_32__ {int /*<<< orphan*/  used; } ;
struct TYPE_24__ {TYPE_11__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL () ; 
 int ONLY_IF_RO ; 
 int ONLY_IF_RW ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_LOAD ; 
 int SEC_NEVER_LOAD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_input_sections (TYPE_11__*,TYPE_12__*) ; 
 TYPE_18__ constructor_list ; 
 int /*<<< orphan*/  exp_init_os (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_os (TYPE_12__*,int /*<<< orphan*/ *,int) ; 
#define  lang_address_statement_enum 143 
#define  lang_afile_asection_pair_statement_enum 142 
#define  lang_assignment_statement_enum 141 
#define  lang_constructors_statement_enum 140 
#define  lang_data_statement_enum 139 
#define  lang_fill_statement_enum 138 
#define  lang_group_statement_enum 137 
#define  lang_input_section_enum 136 
#define  lang_input_statement_enum 135 
#define  lang_object_symbols_statement_enum 134 
#define  lang_output_section_statement_enum 133 
 TYPE_12__* lang_output_section_statement_lookup (int /*<<< orphan*/ ) ; 
#define  lang_output_statement_enum 132 
#define  lang_padding_statement_enum 131 
#define  lang_reloc_statement_enum 130 
#define  lang_target_statement_enum 129 
#define  lang_wild_statement_enum 128 
 int /*<<< orphan*/  wild (int /*<<< orphan*/ *,char const*,TYPE_12__*) ; 

__attribute__((used)) static void
map_input_to_output_sections
  (lang_statement_union_type *s, const char *target,
   lang_output_section_statement_type *os)
{
  flagword flags;

  for (; s != NULL; s = s->header.next)
    {
      switch (s->header.type)
	{
	case lang_wild_statement_enum:
	  wild (&s->wild_statement, target, os);
	  break;
	case lang_constructors_statement_enum:
	  map_input_to_output_sections (constructor_list.head,
					target,
					os);
	  break;
	case lang_output_section_statement_enum:
	  if (s->output_section_statement.constraint)
	    {
	      if (s->output_section_statement.constraint != ONLY_IF_RW
		  && s->output_section_statement.constraint != ONLY_IF_RO)
		break;
	      s->output_section_statement.all_input_readonly = TRUE;
	      check_input_sections (s->output_section_statement.children.head,
				    &s->output_section_statement);
	      if ((s->output_section_statement.all_input_readonly
		   && s->output_section_statement.constraint == ONLY_IF_RW)
		  || (!s->output_section_statement.all_input_readonly
		      && s->output_section_statement.constraint == ONLY_IF_RO))
		{
		  s->output_section_statement.constraint = -1;
		  break;
		}
	    }

	  map_input_to_output_sections (s->output_section_statement.children.head,
					target,
					&s->output_section_statement);
	  break;
	case lang_output_statement_enum:
	  break;
	case lang_target_statement_enum:
	  target = s->target_statement.target;
	  break;
	case lang_group_statement_enum:
	  map_input_to_output_sections (s->group_statement.children.head,
					target,
					os);
	  break;
	case lang_data_statement_enum:
	  /* Make sure that any sections mentioned in the expression
	     are initialized.  */
	  exp_init_os (s->data_statement.exp);
	  flags = SEC_HAS_CONTENTS;
	  /* The output section gets contents, and then we inspect for
	     any flags set in the input script which override any ALLOC.  */
	  if (!(os->flags & SEC_NEVER_LOAD))
	    flags |= SEC_ALLOC | SEC_LOAD;
	  if (os->bfd_section == NULL)
	    init_os (os, NULL, flags);
	  else
	    os->bfd_section->flags |= flags;
	  break;
	case lang_input_section_enum:
	  break;
	case lang_fill_statement_enum:
	case lang_object_symbols_statement_enum:
	case lang_reloc_statement_enum:
	case lang_padding_statement_enum:
	case lang_input_statement_enum:
	  if (os != NULL && os->bfd_section == NULL)
	    init_os (os, NULL, 0);
	  break;
	case lang_assignment_statement_enum:
	  if (os != NULL && os->bfd_section == NULL)
	    init_os (os, NULL, 0);

	  /* Make sure that any sections mentioned in the assignment
	     are initialized.  */
	  exp_init_os (s->assignment_statement.exp);
	  break;
	case lang_afile_asection_pair_statement_enum:
	  FAIL ();
	  break;
	case lang_address_statement_enum:
	  /* Mark the specified section with the supplied address.

	     If this section was actually a segment marker, then the
	     directive is ignored if the linker script explicitly
	     processed the segment marker.  Originally, the linker
	     treated segment directives (like -Ttext on the
	     command-line) as section directives.  We honor the
	     section directive semantics for backwards compatibilty;
	     linker scripts that do not specifically check for
	     SEGMENT_START automatically get the old semantics.  */
	  if (!s->address_statement.segment
	      || !s->address_statement.segment->used)
	    {
	      lang_output_section_statement_type *aos
		= (lang_output_section_statement_lookup
		   (s->address_statement.section_name));

	      if (aos->bfd_section == NULL)
		init_os (aos, NULL, 0);
	      aos->addr_tree = s->address_statement.address;
	    }
	  break;
	}
    }
}