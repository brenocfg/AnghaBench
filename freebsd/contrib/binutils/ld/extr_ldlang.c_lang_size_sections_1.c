#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_78__   TYPE_9__ ;
typedef  struct TYPE_77__   TYPE_8__ ;
typedef  struct TYPE_76__   TYPE_7__ ;
typedef  struct TYPE_75__   TYPE_6__ ;
typedef  struct TYPE_74__   TYPE_5__ ;
typedef  struct TYPE_73__   TYPE_4__ ;
typedef  struct TYPE_72__   TYPE_42__ ;
typedef  struct TYPE_71__   TYPE_41__ ;
typedef  struct TYPE_70__   TYPE_40__ ;
typedef  struct TYPE_69__   TYPE_3__ ;
typedef  struct TYPE_68__   TYPE_37__ ;
typedef  struct TYPE_67__   TYPE_32__ ;
typedef  struct TYPE_66__   TYPE_2__ ;
typedef  struct TYPE_65__   TYPE_27__ ;
typedef  struct TYPE_64__   TYPE_21__ ;
typedef  struct TYPE_63__   TYPE_20__ ;
typedef  struct TYPE_62__   TYPE_1__ ;
typedef  struct TYPE_61__   TYPE_19__ ;
typedef  struct TYPE_60__   TYPE_18__ ;
typedef  struct TYPE_59__   TYPE_17__ ;
typedef  struct TYPE_58__   TYPE_16__ ;
typedef  struct TYPE_57__   TYPE_15__ ;
typedef  struct TYPE_56__   TYPE_14__ ;
typedef  struct TYPE_55__   TYPE_13__ ;
typedef  struct TYPE_54__   TYPE_12__ ;
typedef  struct TYPE_53__   TYPE_11__ ;
typedef  struct TYPE_52__   TYPE_10__ ;

/* Type definitions */
struct TYPE_58__ {int type; TYPE_17__* next; } ;
struct TYPE_56__ {TYPE_17__* head; } ;
struct TYPE_57__ {TYPE_14__ children; } ;
struct TYPE_55__ {unsigned int output_offset; int /*<<< orphan*/  size; } ;
struct TYPE_52__ {TYPE_20__* exp; } ;
struct TYPE_78__ {int /*<<< orphan*/ * fill; TYPE_21__* output_section; } ;
struct TYPE_77__ {TYPE_21__* section; } ;
struct TYPE_75__ {TYPE_17__* head; } ;
struct TYPE_76__ {TYPE_6__ children; } ;
struct TYPE_74__ {unsigned int output_offset; int /*<<< orphan*/  howto; TYPE_21__* output_section; } ;
struct TYPE_73__ {unsigned int output_offset; int /*<<< orphan*/  type; TYPE_20__* exp; TYPE_21__* output_section; } ;
struct TYPE_69__ {TYPE_17__* head; } ;
struct TYPE_60__ {int section_alignment; unsigned int block_value; int section_relative_symbol; int flags; TYPE_21__* bfd_section; int /*<<< orphan*/  ignored; int /*<<< orphan*/ * fill; TYPE_19__* lma_region; TYPE_19__* region; TYPE_20__* addr_tree; TYPE_20__* update_dot_tree; void* processed_lma; int /*<<< orphan*/  sectype; int /*<<< orphan*/  name; int /*<<< orphan*/  load_base; void* processed_vma; TYPE_3__ children; } ;
struct TYPE_59__ {TYPE_16__ header; TYPE_15__ group_statement; TYPE_13__ padding_statement; TYPE_10__ assignment_statement; TYPE_9__ fill_statement; TYPE_8__ input_section; TYPE_7__ wild_statement; TYPE_5__ reloc_statement; TYPE_4__ data_statement; TYPE_18__ output_section_statement; } ;
typedef  TYPE_17__ lang_statement_union_type ;
typedef  TYPE_18__ lang_output_section_statement_type ;
struct TYPE_61__ {char* name; unsigned int current; TYPE_17__* last_os; } ;
typedef  TYPE_19__ lang_memory_region_type ;
typedef  int /*<<< orphan*/  fill_type ;
struct TYPE_54__ {char* dst; } ;
struct TYPE_53__ {int /*<<< orphan*/  node_class; } ;
struct TYPE_63__ {TYPE_12__ assign; TYPE_11__ type; } ;
typedef  TYPE_20__ etree_type ;
typedef  unsigned int bfd_vma ;
typedef  void* bfd_boolean ;
struct TYPE_64__ {int flags; unsigned int size; unsigned int vma; int alignment_power; unsigned int lma; int /*<<< orphan*/  owner; int /*<<< orphan*/  output_offset; } ;
typedef  TYPE_21__ asection ;
struct TYPE_72__ {int /*<<< orphan*/  check_section_addresses; } ;
struct TYPE_71__ {int /*<<< orphan*/  warn_section_align; } ;
struct TYPE_70__ {TYPE_17__* head; } ;
struct TYPE_66__ {unsigned int value; TYPE_1__* section; int /*<<< orphan*/  valid_p; } ;
struct TYPE_68__ {int /*<<< orphan*/  phase; TYPE_2__ result; } ;
struct TYPE_67__ {char* name; int /*<<< orphan*/ * next; } ;
struct TYPE_65__ {TYPE_21__* create_object_symbols_section; int /*<<< orphan*/  relocatable; } ;
struct TYPE_62__ {unsigned int vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  BYTE 147 
 unsigned int BYTE_SIZE ; 
 int /*<<< orphan*/  DEFAULT_MEMORY_REGION ; 
 int /*<<< orphan*/  FAIL () ; 
 void* FALSE ; 
 int /*<<< orphan*/  IGNORE_SECTION (TYPE_21__*) ; 
#define  LONG 146 
 unsigned int LONG_SIZE ; 
#define  QUAD 145 
 unsigned int QUAD_SIZE ; 
 int SEC_ALLOC ; 
 int SEC_COFF_SHARED_LIBRARY ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_LOAD ; 
 int SEC_NEVER_LOAD ; 
 int SEC_THREAD_LOCAL ; 
#define  SHORT 144 
 unsigned int SHORT_SIZE ; 
#define  SQUAD 143 
 unsigned int TO_ADDR (int) ; 
 unsigned int TO_SIZE (unsigned int) ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_18__* abs_output_section ; 
 unsigned int align_power (unsigned int,int) ; 
 TYPE_21__* bfd_abs_section_ptr ; 
 int /*<<< orphan*/  bfd_get_flavour (int /*<<< orphan*/ ) ; 
 int bfd_get_reloc_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_section_name (int /*<<< orphan*/ ,TYPE_21__*) ; 
 int /*<<< orphan*/  bfd_is_abs_section (TYPE_21__*) ; 
 int /*<<< orphan*/  bfd_relax_section (int /*<<< orphan*/ ,TYPE_21__*,TYPE_27__*,void**) ; 
 unsigned int bfd_section_vma (int /*<<< orphan*/ ,TYPE_21__*) ; 
 int /*<<< orphan*/  bfd_set_section_vma (int /*<<< orphan*/ ,TYPE_21__*,unsigned int) ; 
 int /*<<< orphan*/  bfd_target_coff_flavour ; 
 int /*<<< orphan*/  bfd_target_ecoff_flavour ; 
 TYPE_42__ command_line ; 
 TYPE_41__ config ; 
 TYPE_40__ constructor_list ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  etree_assign ; 
 int /*<<< orphan*/  etree_provided ; 
 int /*<<< orphan*/  exp_fold_tree (TYPE_20__*,TYPE_21__*,unsigned int*) ; 
 unsigned int exp_get_abs_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_37__ expld ; 
 int /*<<< orphan*/  insert_pad (TYPE_17__**,int /*<<< orphan*/ *,unsigned int,TYPE_21__*,unsigned int) ; 
#define  lang_address_statement_enum 142 
#define  lang_assignment_statement_enum 141 
#define  lang_constructors_statement_enum 140 
#define  lang_data_statement_enum 139 
#define  lang_fill_statement_enum 138 
#define  lang_group_statement_enum 137 
#define  lang_input_section_enum 136 
#define  lang_input_statement_enum 135 
 int /*<<< orphan*/  lang_mark_phase_enum ; 
 TYPE_19__* lang_memory_default (TYPE_21__*) ; 
 TYPE_32__* lang_memory_region_list ; 
 TYPE_19__* lang_memory_region_lookup (int /*<<< orphan*/ ,void*) ; 
#define  lang_object_symbols_statement_enum 134 
#define  lang_output_section_statement_enum 133 
#define  lang_output_statement_enum 132 
#define  lang_padding_statement_enum 131 
#define  lang_reloc_statement_enum 130 
#define  lang_target_statement_enum 129 
#define  lang_wild_statement_enum 128 
 TYPE_27__ link_info ; 
 int /*<<< orphan*/  os_region_check (TYPE_18__*,TYPE_19__*,TYPE_20__*,unsigned int) ; 
 int /*<<< orphan*/  output_bfd ; 
 int /*<<< orphan*/  overlay_section ; 
 unsigned int size_input_section (TYPE_17__**,TYPE_18__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_vma
lang_size_sections_1
  (lang_statement_union_type *s,
   lang_output_section_statement_type *output_section_statement,
   lang_statement_union_type **prev,
   fill_type *fill,
   bfd_vma dot,
   bfd_boolean *relax,
   bfd_boolean check_regions)
{
  /* Size up the sections from their constituent parts.  */
  for (; s != NULL; s = s->header.next)
    {
      switch (s->header.type)
	{
	case lang_output_section_statement_enum:
	  {
	    bfd_vma newdot, after;
	    lang_output_section_statement_type *os;
	    lang_memory_region_type *r;

	    os = &s->output_section_statement;
	    if (os->addr_tree != NULL)
	      {
		os->processed_vma = FALSE;
		exp_fold_tree (os->addr_tree, bfd_abs_section_ptr, &dot);

		if (!expld.result.valid_p
		    && expld.phase != lang_mark_phase_enum)
		  einfo (_("%F%S: non constant or forward reference"
			   " address expression for section %s\n"),
			 os->name);

		dot = expld.result.value + expld.result.section->vma;
	      }

	    if (os->bfd_section == NULL)
	      /* This section was removed or never actually created.  */
	      break;

	    /* If this is a COFF shared library section, use the size and
	       address from the input section.  FIXME: This is COFF
	       specific; it would be cleaner if there were some other way
	       to do this, but nothing simple comes to mind.  */
	    if ((bfd_get_flavour (output_bfd) == bfd_target_ecoff_flavour
		 || bfd_get_flavour (output_bfd) == bfd_target_coff_flavour)
		&& (os->bfd_section->flags & SEC_COFF_SHARED_LIBRARY) != 0)
	      {
		asection *input;

		if (os->children.head == NULL
		    || os->children.head->header.next != NULL
		    || (os->children.head->header.type
			!= lang_input_section_enum))
		  einfo (_("%P%X: Internal error on COFF shared library"
			   " section %s\n"), os->name);

		input = os->children.head->input_section.section;
		(void) bfd_set_section_vma (os->bfd_section->owner,
					    os->bfd_section,
					    bfd_section_vma (input->owner,
							     input));
		os->bfd_section->size = input->size;
		break;
	      }

	    newdot = dot;
	    if (bfd_is_abs_section (os->bfd_section))
	      {
		/* No matter what happens, an abs section starts at zero.  */
		ASSERT (os->bfd_section->vma == 0);
	      }
	    else
	      {
		int align;

		if (os->addr_tree == NULL)
		  {
		    /* No address specified for this section, get one
		       from the region specification.  */
		    if (os->region == NULL
			|| ((os->bfd_section->flags & (SEC_ALLOC | SEC_LOAD))
			    && os->region->name[0] == '*'
			    && strcmp (os->region->name,
				       DEFAULT_MEMORY_REGION) == 0))
		      {
			os->region = lang_memory_default (os->bfd_section);
		      }

		    /* If a loadable section is using the default memory
		       region, and some non default memory regions were
		       defined, issue an error message.  */
		    if (!os->ignored
			&& !IGNORE_SECTION (os->bfd_section)
			&& ! link_info.relocatable
			&& check_regions
			&& strcmp (os->region->name,
				   DEFAULT_MEMORY_REGION) == 0
			&& lang_memory_region_list != NULL
			&& (strcmp (lang_memory_region_list->name,
				    DEFAULT_MEMORY_REGION) != 0
			    || lang_memory_region_list->next != NULL)
			&& expld.phase != lang_mark_phase_enum)
		      {
			/* By default this is an error rather than just a
			   warning because if we allocate the section to the
			   default memory region we can end up creating an
			   excessively large binary, or even seg faulting when
			   attempting to perform a negative seek.  See
			   sources.redhat.com/ml/binutils/2003-04/msg00423.html
			   for an example of this.  This behaviour can be
			   overridden by the using the --no-check-sections
			   switch.  */
			if (command_line.check_section_addresses)
			  einfo (_("%P%F: error: no memory region specified"
				   " for loadable section `%s'\n"),
				 bfd_get_section_name (output_bfd,
						       os->bfd_section));
			else
			  einfo (_("%P: warning: no memory region specified"
				   " for loadable section `%s'\n"),
				 bfd_get_section_name (output_bfd,
						       os->bfd_section));
		      }

		    newdot = os->region->current;
		    align = os->bfd_section->alignment_power;
		  }
		else
		  align = os->section_alignment;

		/* Align to what the section needs.  */
		if (align > 0)
		  {
		    bfd_vma savedot = newdot;
		    newdot = align_power (newdot, align);

		    if (newdot != savedot
			&& (config.warn_section_align
			    || os->addr_tree != NULL)
			&& expld.phase != lang_mark_phase_enum)
		      einfo (_("%P: warning: changing start of section"
			       " %s by %lu bytes\n"),
			     os->name, (unsigned long) (newdot - savedot));
		  }

		(void) bfd_set_section_vma (0, os->bfd_section, newdot);

		os->bfd_section->output_offset = 0;
	      }

	    lang_size_sections_1 (os->children.head, os, &os->children.head,
				  os->fill, newdot, relax, check_regions);

	    os->processed_vma = TRUE;

	    if (bfd_is_abs_section (os->bfd_section) || os->ignored)
	      /* Except for some special linker created sections,
		 no output section should change from zero size
		 after strip_excluded_output_sections.  A non-zero
		 size on an ignored section indicates that some
		 input section was not sized early enough.  */
	      ASSERT (os->bfd_section->size == 0);
	    else
	      {
		dot = os->bfd_section->vma;

		/* Put the section within the requested block size, or
		   align at the block boundary.  */
		after = ((dot
			  + TO_ADDR (os->bfd_section->size)
			  + os->block_value - 1)
			 & - (bfd_vma) os->block_value);

		os->bfd_section->size = TO_SIZE (after - os->bfd_section->vma);
	      }

	    /* Set section lma.  */
	    r = os->region;
	    if (r == NULL)
	      r = lang_memory_region_lookup (DEFAULT_MEMORY_REGION, FALSE);

	    if (os->load_base)
	      {
		bfd_vma lma = exp_get_abs_int (os->load_base, 0, "load base");
		os->bfd_section->lma = lma;
	      }
	    else if (os->region != NULL
		     && os->lma_region != NULL
		     && os->lma_region != os->region)
	      {
		bfd_vma lma = os->lma_region->current;

		if (os->section_alignment != -1)
		  lma = align_power (lma, os->section_alignment);
		os->bfd_section->lma = lma;
	      }
	    else if (r->last_os != NULL
		     && (os->bfd_section->flags & SEC_ALLOC) != 0)
	      {
		bfd_vma lma;
		asection *last;

		last = r->last_os->output_section_statement.bfd_section;

		/* A backwards move of dot should be accompanied by
		   an explicit assignment to the section LMA (ie.
		   os->load_base set) because backwards moves can
		   create overlapping LMAs.  */
		if (dot < last->vma
		    && os->bfd_section->size != 0
		    && dot + os->bfd_section->size <= last->vma)
		  {
		    /* If dot moved backwards then leave lma equal to
		       vma.  This is the old default lma, which might
		       just happen to work when the backwards move is
		       sufficiently large.  Nag if this changes anything,
		       so people can fix their linker scripts.  */

		    if (last->vma != last->lma)
		      einfo (_("%P: warning: dot moved backwards before `%s'\n"),
			     os->name);
		  }
		else
		  {
		    /* If this is an overlay, set the current lma to that
		       at the end of the previous section.  */
		    if (os->sectype == overlay_section)
		      lma = last->lma + last->size;

		    /* Otherwise, keep the same lma to vma relationship
		       as the previous section.  */
		    else
		      lma = dot + last->lma - last->vma;

		    if (os->section_alignment != -1)
		      lma = align_power (lma, os->section_alignment);
		    os->bfd_section->lma = lma;
		  }
	      }
	    os->processed_lma = TRUE;

	    if (bfd_is_abs_section (os->bfd_section) || os->ignored)
	      break;

	    /* Keep track of normal sections using the default
	       lma region.  We use this to set the lma for
	       following sections.  Overlays or other linker
	       script assignment to lma might mean that the
	       default lma == vma is incorrect.
	       To avoid warnings about dot moving backwards when using
	       -Ttext, don't start tracking sections until we find one
	       of non-zero size or with lma set differently to vma.  */
	    if (((os->bfd_section->flags & SEC_HAS_CONTENTS) != 0
		 || (os->bfd_section->flags & SEC_THREAD_LOCAL) == 0)
		&& (os->bfd_section->flags & SEC_ALLOC) != 0
		&& (os->bfd_section->size != 0
		    || (r->last_os == NULL
			&& os->bfd_section->vma != os->bfd_section->lma)
		    || (r->last_os != NULL
			&& dot >= (r->last_os->output_section_statement
				   .bfd_section->vma)))
		&& os->lma_region == NULL
		&& !link_info.relocatable)
	      r->last_os = s;

	    /* .tbss sections effectively have zero size.  */
	    if ((os->bfd_section->flags & SEC_HAS_CONTENTS) != 0
		|| (os->bfd_section->flags & SEC_THREAD_LOCAL) == 0
		|| link_info.relocatable)
	      dot += TO_ADDR (os->bfd_section->size);

	    if (os->update_dot_tree != 0)
	      exp_fold_tree (os->update_dot_tree, bfd_abs_section_ptr, &dot);

	    /* Update dot in the region ?
	       We only do this if the section is going to be allocated,
	       since unallocated sections do not contribute to the region's
	       overall size in memory.

	       If the SEC_NEVER_LOAD bit is not set, it will affect the
	       addresses of sections after it. We have to update
	       dot.  */
	    if (os->region != NULL
		&& ((os->bfd_section->flags & SEC_NEVER_LOAD) == 0
		    || (os->bfd_section->flags & (SEC_ALLOC | SEC_LOAD))))
	      {
		os->region->current = dot;

		if (check_regions)
		  /* Make sure the new address is within the region.  */
		  os_region_check (os, os->region, os->addr_tree,
				   os->bfd_section->vma);

		if (os->lma_region != NULL && os->lma_region != os->region)
		  {
		    os->lma_region->current
		      = os->bfd_section->lma + TO_ADDR (os->bfd_section->size);

		    if (check_regions)
		      os_region_check (os, os->lma_region, NULL,
				       os->bfd_section->lma);
		  }
	      }
	  }
	  break;

	case lang_constructors_statement_enum:
	  dot = lang_size_sections_1 (constructor_list.head,
				      output_section_statement,
				      &s->wild_statement.children.head,
				      fill, dot, relax, check_regions);
	  break;

	case lang_data_statement_enum:
	  {
	    unsigned int size = 0;

	    s->data_statement.output_offset =
	      dot - output_section_statement->bfd_section->vma;
	    s->data_statement.output_section =
	      output_section_statement->bfd_section;

	    /* We might refer to provided symbols in the expression, and
	       need to mark them as needed.  */
	    exp_fold_tree (s->data_statement.exp, bfd_abs_section_ptr, &dot);

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
	    output_section_statement->bfd_section->size += size;
	  }
	  break;

	case lang_reloc_statement_enum:
	  {
	    int size;

	    s->reloc_statement.output_offset =
	      dot - output_section_statement->bfd_section->vma;
	    s->reloc_statement.output_section =
	      output_section_statement->bfd_section;
	    size = bfd_get_reloc_size (s->reloc_statement.howto);
	    dot += TO_ADDR (size);
	    output_section_statement->bfd_section->size += size;
	  }
	  break;

	case lang_wild_statement_enum:
	  dot = lang_size_sections_1 (s->wild_statement.children.head,
				      output_section_statement,
				      &s->wild_statement.children.head,
				      fill, dot, relax, check_regions);
	  break;

	case lang_object_symbols_statement_enum:
	  link_info.create_object_symbols_section =
	    output_section_statement->bfd_section;
	  break;

	case lang_output_statement_enum:
	case lang_target_statement_enum:
	  break;

	case lang_input_section_enum:
	  {
	    asection *i;

	    i = (*prev)->input_section.section;
	    if (relax)
	      {
		bfd_boolean again;

		if (! bfd_relax_section (i->owner, i, &link_info, &again))
		  einfo (_("%P%F: can't relax section: %E\n"));
		if (again)
		  *relax = TRUE;
	      }
	    dot = size_input_section (prev, output_section_statement,
				      output_section_statement->fill, dot);
	  }
	  break;

	case lang_input_statement_enum:
	  break;

	case lang_fill_statement_enum:
	  s->fill_statement.output_section =
	    output_section_statement->bfd_section;

	  fill = s->fill_statement.fill;
	  break;

	case lang_assignment_statement_enum:
	  {
	    bfd_vma newdot = dot;
	    etree_type *tree = s->assignment_statement.exp;

	    exp_fold_tree (tree,
			   output_section_statement->bfd_section,
			   &newdot);

	    /* This symbol is relative to this section.  */
	    if ((tree->type.node_class == etree_provided
		 || tree->type.node_class == etree_assign)
		&& (tree->assign.dst [0] != '.'
		    || tree->assign.dst [1] != '\0'))
	      output_section_statement->section_relative_symbol = 1;

	    if (!output_section_statement->ignored)
	      {
		if (output_section_statement == abs_output_section)
		  {
		    /* If we don't have an output section, then just adjust
		       the default memory address.  */
		    lang_memory_region_lookup (DEFAULT_MEMORY_REGION,
					       FALSE)->current = newdot;
		  }
		else if (newdot != dot)
		  {
		    /* Insert a pad after this statement.  We can't
		       put the pad before when relaxing, in case the
		       assignment references dot.  */
		    insert_pad (&s->header.next, fill, TO_SIZE (newdot - dot),
				output_section_statement->bfd_section, dot);

		    /* Don't neuter the pad below when relaxing.  */
		    s = s->header.next;

		    /* If dot is advanced, this implies that the section
		       should have space allocated to it, unless the
		       user has explicitly stated that the section
		       should never be loaded.  */
		    if (!(output_section_statement->flags
			  & (SEC_NEVER_LOAD | SEC_ALLOC)))
		      output_section_statement->bfd_section->flags |= SEC_ALLOC;
		  }
		dot = newdot;
	      }
	  }
	  break;

	case lang_padding_statement_enum:
	  /* If this is the first time lang_size_sections is called,
	     we won't have any padding statements.  If this is the
	     second or later passes when relaxing, we should allow
	     padding to shrink.  If padding is needed on this pass, it
	     will be added back in.  */
	  s->padding_statement.size = 0;

	  /* Make sure output_offset is valid.  If relaxation shrinks
	     the section and this pad isn't needed, it's possible to
	     have output_offset larger than the final size of the
	     section.  bfd_set_section_contents will complain even for
	     a pad size of zero.  */
	  s->padding_statement.output_offset
	    = dot - output_section_statement->bfd_section->vma;
	  break;

	case lang_group_statement_enum:
	  dot = lang_size_sections_1 (s->group_statement.children.head,
				      output_section_statement,
				      &s->group_statement.children.head,
				      fill, dot, relax, check_regions);
	  break;

	default:
	  FAIL ();
	  break;

	  /* We can only get here when relaxing is turned on.  */
	case lang_address_statement_enum:
	  break;
	}
      prev = &s->header.next;
    }
  return dot;
}