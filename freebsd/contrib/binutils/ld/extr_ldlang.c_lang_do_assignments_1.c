#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_23__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_21__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_15__* head; } ;
struct TYPE_29__ {TYPE_13__ children; } ;
struct TYPE_27__ {unsigned int size; } ;
struct TYPE_26__ {int /*<<< orphan*/  exp; } ;
struct TYPE_25__ {int /*<<< orphan*/ * fill; } ;
struct TYPE_45__ {TYPE_17__* section; } ;
struct TYPE_44__ {int /*<<< orphan*/  howto; scalar_t__ addend_value; int /*<<< orphan*/  addend_exp; } ;
struct TYPE_42__ {int /*<<< orphan*/  type; scalar_t__ value; int /*<<< orphan*/  exp; } ;
struct TYPE_39__ {TYPE_15__* head; } ;
struct TYPE_40__ {TYPE_3__ children; } ;
struct TYPE_38__ {TYPE_15__* head; } ;
struct TYPE_31__ {TYPE_22__* bfd_section; int /*<<< orphan*/ * fill; TYPE_2__ children; int /*<<< orphan*/  ignored; } ;
struct TYPE_34__ {int type; TYPE_15__* next; } ;
struct TYPE_30__ {TYPE_14__ group_statement; TYPE_12__ padding_statement; TYPE_11__ assignment_statement; TYPE_10__ fill_statement; TYPE_9__ input_section; TYPE_8__ reloc_statement; TYPE_6__ data_statement; TYPE_4__ wild_statement; TYPE_16__ output_section_statement; TYPE_1__ header; } ;
typedef  TYPE_15__ lang_statement_union_type ;
typedef  TYPE_16__ lang_output_section_statement_type ;
typedef  int /*<<< orphan*/  fill_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_32__ {int flags; unsigned int size; } ;
typedef  TYPE_17__ asection ;
struct TYPE_43__ {scalar_t__ value; int /*<<< orphan*/  valid_p; TYPE_5__* section; } ;
struct TYPE_41__ {scalar_t__ vma; } ;
struct TYPE_37__ {TYPE_15__* head; } ;
struct TYPE_36__ {int flags; unsigned int size; int /*<<< orphan*/  vma; } ;
struct TYPE_35__ {TYPE_7__ result; } ;
struct TYPE_33__ {int /*<<< orphan*/  relocatable; } ;

/* Variables and functions */
#define  BYTE 147 
 unsigned int BYTE_SIZE ; 
 int /*<<< orphan*/  FAIL () ; 
#define  LONG 146 
 unsigned int LONG_SIZE ; 
#define  QUAD 145 
 unsigned int QUAD_SIZE ; 
 int SEC_EXCLUDE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_THREAD_LOCAL ; 
#define  SHORT 144 
 unsigned int SHORT_SIZE ; 
#define  SQUAD 143 
 int /*<<< orphan*/  TO_ADDR (unsigned int) ; 
 unsigned int TO_SIZE (unsigned int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_22__* bfd_abs_section_ptr ; 
 unsigned int bfd_get_reloc_size (int /*<<< orphan*/ ) ; 
 TYPE_23__ constructor_list ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exp_fold_tree (int /*<<< orphan*/ ,TYPE_22__*,int /*<<< orphan*/ *) ; 
 TYPE_21__ expld ; 
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
 TYPE_18__ link_info ; 

__attribute__((used)) static bfd_vma
lang_do_assignments_1 (lang_statement_union_type *s,
		       lang_output_section_statement_type *current_os,
		       fill_type *fill,
		       bfd_vma dot)
{
  for (; s != NULL; s = s->header.next)
    {
      switch (s->header.type)
	{
	case lang_constructors_statement_enum:
	  dot = lang_do_assignments_1 (constructor_list.head,
				       current_os, fill, dot);
	  break;

	case lang_output_section_statement_enum:
	  {
	    lang_output_section_statement_type *os;

	    os = &(s->output_section_statement);
	    if (os->bfd_section != NULL && !os->ignored)
	      {
		dot = os->bfd_section->vma;

		lang_do_assignments_1 (os->children.head, os, os->fill, dot);

		/* .tbss sections effectively have zero size.  */
		if ((os->bfd_section->flags & SEC_HAS_CONTENTS) != 0
		    || (os->bfd_section->flags & SEC_THREAD_LOCAL) == 0
		    || link_info.relocatable)
		  dot += TO_ADDR (os->bfd_section->size);
	      }
	  }
	  break;

	case lang_wild_statement_enum:

	  dot = lang_do_assignments_1 (s->wild_statement.children.head,
				       current_os, fill, dot);
	  break;

	case lang_object_symbols_statement_enum:
	case lang_output_statement_enum:
	case lang_target_statement_enum:
	  break;

	case lang_data_statement_enum:
	  exp_fold_tree (s->data_statement.exp, bfd_abs_section_ptr, &dot);
	  if (expld.result.valid_p)
	    s->data_statement.value = (expld.result.value
				       + expld.result.section->vma);
	  else
	    einfo (_("%F%P: invalid data statement\n"));
	  {
	    unsigned int size;
	    switch (s->data_statement.type)
	      {
	      default:
		abort ();
	      case QUAD:
	      case SQUAD:
		size = QUAD_SIZE;
		break;
	      case LONG:
		size = LONG_SIZE;
		break;
	      case SHORT:
		size = SHORT_SIZE;
		break;
	      case BYTE:
		size = BYTE_SIZE;
		break;
	      }
	    if (size < TO_SIZE ((unsigned) 1))
	      size = TO_SIZE ((unsigned) 1);
	    dot += TO_ADDR (size);
	  }
	  break;

	case lang_reloc_statement_enum:
	  exp_fold_tree (s->reloc_statement.addend_exp,
			 bfd_abs_section_ptr, &dot);
	  if (expld.result.valid_p)
	    s->reloc_statement.addend_value = expld.result.value;
	  else
	    einfo (_("%F%P: invalid reloc statement\n"));
	  dot += TO_ADDR (bfd_get_reloc_size (s->reloc_statement.howto));
	  break;

	case lang_input_section_enum:
	  {
	    asection *in = s->input_section.section;

	    if ((in->flags & SEC_EXCLUDE) == 0)
	      dot += TO_ADDR (in->size);
	  }
	  break;

	case lang_input_statement_enum:
	  break;

	case lang_fill_statement_enum:
	  fill = s->fill_statement.fill;
	  break;

	case lang_assignment_statement_enum:
	  exp_fold_tree (s->assignment_statement.exp,
			 current_os->bfd_section,
			 &dot);
	  break;

	case lang_padding_statement_enum:
	  dot += TO_ADDR (s->padding_statement.size);
	  break;

	case lang_group_statement_enum:
	  dot = lang_do_assignments_1 (s->group_statement.children.head,
				       current_os, fill, dot);
	  break;

	default:
	  FAIL ();
	  break;

	case lang_address_statement_enum:
	  break;
	}
    }
  return dot;
}