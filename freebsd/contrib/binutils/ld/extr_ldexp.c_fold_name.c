#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_20__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_19__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/ * next; int /*<<< orphan*/ * abfd; } ;
struct TYPE_27__ {int value; TYPE_20__* section; } ;
struct TYPE_29__ {TYPE_3__ undef; TYPE_2__ def; } ;
struct bfd_link_hash_entry {TYPE_4__ u; int /*<<< orphan*/  type; } ;
struct TYPE_31__ {TYPE_9__* bfd_section; int /*<<< orphan*/  processed_vma; int /*<<< orphan*/ * load_base; int /*<<< orphan*/  processed_lma; } ;
typedef  TYPE_6__ lang_output_section_statement_type ;
struct TYPE_32__ {int length; int origin; } ;
typedef  TYPE_7__ lang_memory_region_type ;
struct TYPE_30__ {char* name; } ;
struct TYPE_25__ {int node_code; } ;
struct TYPE_33__ {TYPE_5__ name; TYPE_1__ type; } ;
typedef  TYPE_8__ etree_type ;
typedef  int bfd_vma ;
struct TYPE_34__ {int lma; int size; int alignment_power; } ;
typedef  TYPE_9__ asection ;
struct TYPE_26__ {int output_offset; TYPE_9__* output_section; } ;
struct TYPE_24__ {struct bfd_link_hash_entry* undefs_tail; } ;
struct TYPE_21__ {int value; int /*<<< orphan*/  valid_p; int /*<<< orphan*/  section; } ;
struct TYPE_23__ {int /*<<< orphan*/  phase; int /*<<< orphan*/  assigning_to_dot; int /*<<< orphan*/  dot; TYPE_11__ result; } ;
struct TYPE_22__ {TYPE_19__* hash; } ;

/* Variables and functions */
#define  ADDR 137 
#define  ALIGNOF 136 
#define  CONSTANT 135 
#define  DEFINED 134 
 int /*<<< orphan*/  FAIL () ; 
 int /*<<< orphan*/  FALSE ; 
#define  LENGTH 133 
#define  LOADADDR 132 
#define  NAME 131 
#define  ORIGIN 130 
#define  SIZEOF 129 
#define  SIZEOF_HEADERS 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_abs_section_ptr ; 
 int bfd_emul_get_commonpagesize (int /*<<< orphan*/ ) ; 
 int bfd_emul_get_maxpagesize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_is_abs_section (TYPE_20__*) ; 
 int /*<<< orphan*/  bfd_link_add_undef (TYPE_19__*,struct bfd_link_hash_entry*) ; 
 int /*<<< orphan*/  bfd_link_hash_common ; 
 int /*<<< orphan*/  bfd_link_hash_defined ; 
 int /*<<< orphan*/  bfd_link_hash_defweak ; 
 int /*<<< orphan*/  bfd_link_hash_new ; 
 int /*<<< orphan*/  bfd_link_hash_undefined ; 
 int bfd_octets_per_byte (int /*<<< orphan*/ ) ; 
 int bfd_sizeof_headers (int /*<<< orphan*/ ,TYPE_12__*) ; 
 struct bfd_link_hash_entry* bfd_wrapped_link_hash_lookup (int /*<<< orphan*/ ,TYPE_12__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_target ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  exp_fold_tree_1 (int /*<<< orphan*/ *) ; 
 TYPE_16__ expld ; 
 int /*<<< orphan*/  lang_final_phase_enum ; 
 int /*<<< orphan*/  lang_first_phase_enum ; 
 int /*<<< orphan*/  lang_mark_phase_enum ; 
 TYPE_7__* lang_memory_region_lookup (char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* lang_output_section_find (char*) ; 
 int lang_statement_iteration ; 
 int lang_symbol_definition_iteration (char*) ; 
 int /*<<< orphan*/  lang_track_definedness (char*) ; 
 TYPE_12__ link_info ; 
 int /*<<< orphan*/  make_abs () ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_abs (int) ; 
 int /*<<< orphan*/  new_rel (int,int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  new_rel_from_abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_bfd ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
fold_name (etree_type *tree)
{
  memset (&expld.result, 0, sizeof (expld.result));

  switch (tree->type.node_code)
    {
    case SIZEOF_HEADERS:
      if (expld.phase != lang_first_phase_enum)
	{
	  bfd_vma hdr_size = 0;
	  /* Don't find the real header size if only marking sections;
	     The bfd function may cache incorrect data.  */
	  if (expld.phase != lang_mark_phase_enum)
	    hdr_size = bfd_sizeof_headers (output_bfd, &link_info);
	  new_abs (hdr_size);
	}
      break;

    case DEFINED:
      if (expld.phase == lang_first_phase_enum)
	lang_track_definedness (tree->name.name);
      else
	{
	  struct bfd_link_hash_entry *h;
	  int def_iteration
	    = lang_symbol_definition_iteration (tree->name.name);

	  h = bfd_wrapped_link_hash_lookup (output_bfd, &link_info,
					    tree->name.name,
					    FALSE, FALSE, TRUE);
	  expld.result.value = (h != NULL
				&& (h->type == bfd_link_hash_defined
				    || h->type == bfd_link_hash_defweak
				    || h->type == bfd_link_hash_common)
				&& (def_iteration == lang_statement_iteration
				    || def_iteration == -1));
	  expld.result.section = bfd_abs_section_ptr;
	  expld.result.valid_p = TRUE;
	}
      break;

    case NAME:
      if (expld.phase == lang_first_phase_enum)
	;
      else if (tree->name.name[0] == '.' && tree->name.name[1] == 0)
	new_rel_from_abs (expld.dot);
      else
	{
	  struct bfd_link_hash_entry *h;

	  h = bfd_wrapped_link_hash_lookup (output_bfd, &link_info,
					    tree->name.name,
					    TRUE, FALSE, TRUE);
	  if (!h)
	    einfo (_("%P%F: bfd_link_hash_lookup failed: %E\n"));
	  else if (h->type == bfd_link_hash_defined
		   || h->type == bfd_link_hash_defweak)
	    {
	      if (bfd_is_abs_section (h->u.def.section))
		new_abs (h->u.def.value);
	      else
		{
		  asection *output_section;

		  output_section = h->u.def.section->output_section;
		  if (output_section == NULL)
		    {
		      if (expld.phase != lang_mark_phase_enum)
			einfo (_("%X%S: unresolvable symbol `%s'"
				 " referenced in expression\n"),
			       tree->name.name);
		    }
		  else
		    new_rel (h->u.def.value + h->u.def.section->output_offset,
			     NULL, output_section);
		}
	    }
	  else if (expld.phase == lang_final_phase_enum
		   || expld.assigning_to_dot)
	    einfo (_("%F%S: undefined symbol `%s' referenced in expression\n"),
		   tree->name.name);
	  else if (h->type == bfd_link_hash_new)
	    {
	      h->type = bfd_link_hash_undefined;
	      h->u.undef.abfd = NULL;
	      if (h->u.undef.next == NULL && h != link_info.hash->undefs_tail)
		bfd_link_add_undef (link_info.hash, h);
	    }
	}
      break;

    case ADDR:
      if (expld.phase != lang_first_phase_enum)
	{
	  lang_output_section_statement_type *os;

	  os = lang_output_section_find (tree->name.name);
	  if (os == NULL)
	    {
	      if (expld.phase == lang_final_phase_enum)
		einfo (_("%F%S: undefined section `%s' referenced in expression\n"),
		       tree->name.name);
	    }
	  else if (os->processed_vma)
	    new_rel (0, NULL, os->bfd_section);
	}
      break;

    case LOADADDR:
      if (expld.phase != lang_first_phase_enum)
	{
	  lang_output_section_statement_type *os;

	  os = lang_output_section_find (tree->name.name);
	  if (os == NULL)
	    {
	      if (expld.phase == lang_final_phase_enum)
		einfo (_("%F%S: undefined section `%s' referenced in expression\n"),
		       tree->name.name);
	    }
	  else if (os->processed_lma)
	    {
	      if (os->load_base == NULL)
		new_abs (os->bfd_section->lma);
	      else
		{
		  exp_fold_tree_1 (os->load_base);
		  make_abs ();
		}
	    }
	}
      break;

    case SIZEOF:
    case ALIGNOF:
      if (expld.phase != lang_first_phase_enum)
	{
	  lang_output_section_statement_type *os;

	  os = lang_output_section_find (tree->name.name);
	  if (os == NULL)
	    {
	      if (expld.phase == lang_final_phase_enum)
		einfo (_("%F%S: undefined section `%s' referenced in expression\n"),
		       tree->name.name);
	      new_abs (0);
	    }
	  else if (os->processed_vma)
	    {
	      bfd_vma val;

	      if (tree->type.node_code == SIZEOF)
		val = os->bfd_section->size / bfd_octets_per_byte (output_bfd);
	      else
		val = (bfd_vma)1 << os->bfd_section->alignment_power;
	      
	      new_abs (val);
	    }
	}
      break;

    case LENGTH:
      {
        lang_memory_region_type *mem;
        
        mem = lang_memory_region_lookup (tree->name.name, FALSE);  
        if (mem != NULL) 
          new_abs (mem->length);
        else          
          einfo (_("%F%S: undefined MEMORY region `%s'"
		   " referenced in expression\n"), tree->name.name);
      }
      break;

    case ORIGIN:
      {
        lang_memory_region_type *mem;
        
        mem = lang_memory_region_lookup (tree->name.name, FALSE);  
        if (mem != NULL) 
          new_abs (mem->origin);
        else          
          einfo (_("%F%S: undefined MEMORY region `%s'"
		   " referenced in expression\n"), tree->name.name);
      }
      break;

    case CONSTANT:
      if (strcmp (tree->name.name, "MAXPAGESIZE") == 0)
	new_abs (bfd_emul_get_maxpagesize (default_target));
      else if (strcmp (tree->name.name, "COMMONPAGESIZE") == 0)
	new_abs (bfd_emul_get_commonpagesize (default_target));
      else
	einfo (_("%F%S: unknown constant `%s' referenced in expression\n"),
	       tree->name.name);
      break;

    default:
      FAIL ();
      break;
    }
}