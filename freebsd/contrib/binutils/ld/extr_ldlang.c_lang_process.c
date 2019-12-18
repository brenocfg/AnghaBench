#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ asection ;
struct TYPE_17__ {scalar_t__ check_section_addresses; scalar_t__ relax; scalar_t__ version_exports_section; } ;
struct TYPE_16__ {scalar_t__ text_read_only; } ;
struct TYPE_15__ {int /*<<< orphan*/ * name; } ;
struct TYPE_14__ {int relax_pass; int /*<<< orphan*/  relocatable; TYPE_5__* gc_sym_list; TYPE_1__* dynamic_list; } ;
struct TYPE_13__ {int /*<<< orphan*/  head; } ;
struct TYPE_11__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEC_READONLY ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_merge_sections (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_section_already_linked_table_free () ; 
 int /*<<< orphan*/  bfd_section_already_linked_table_init () ; 
 TYPE_8__ command_line ; 
 TYPE_7__ config ; 
 int /*<<< orphan*/  current_target ; 
 int /*<<< orphan*/  default_target ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 TYPE_5__ entry_symbol ; 
 int /*<<< orphan*/  init_opb () ; 
 int /*<<< orphan*/  lang_check () ; 
 int /*<<< orphan*/  lang_check_section_addresses () ; 
 int /*<<< orphan*/  lang_common () ; 
 int /*<<< orphan*/  lang_do_assignments () ; 
 int /*<<< orphan*/  lang_do_version_exports_section () ; 
 int /*<<< orphan*/  lang_end () ; 
 int /*<<< orphan*/  lang_finalize_version_expr_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_for_each_statement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_gc_sections () ; 
 int /*<<< orphan*/  lang_place_orphans () ; 
 int /*<<< orphan*/  lang_place_undefineds () ; 
 int /*<<< orphan*/  lang_record_phdrs () ; 
 int /*<<< orphan*/  lang_reset_memory_regions () ; 
 int /*<<< orphan*/  lang_set_startof () ; 
 int /*<<< orphan*/  lang_size_sections (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldctor_build_sets () ; 
 int /*<<< orphan*/  ldemul_after_allocation () ; 
 int /*<<< orphan*/  ldemul_after_open () ; 
 int /*<<< orphan*/  ldemul_before_allocation () ; 
 int /*<<< orphan*/  ldemul_create_output_section_statements () ; 
 int /*<<< orphan*/  ldemul_finish () ; 
 int /*<<< orphan*/  ldlang_open_output ; 
 TYPE_5__* ldlang_undef_chain_list_head ; 
 TYPE_4__ link_info ; 
 int /*<<< orphan*/  map_input_to_output_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_input_bfds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_bfd ; 
 int /*<<< orphan*/  relax_sections () ; 
 TYPE_3__ statement_list ; 
 int /*<<< orphan*/  update_wild_statements (int /*<<< orphan*/ ) ; 

void
lang_process (void)
{
  /* Finalize dynamic list.  */
  if (link_info.dynamic_list)
    lang_finalize_version_expr_head (&link_info.dynamic_list->head);

  current_target = default_target;

  /* Open the output file.  */
  lang_for_each_statement (ldlang_open_output);
  init_opb ();

  ldemul_create_output_section_statements ();

  /* Add to the hash table all undefineds on the command line.  */
  lang_place_undefineds ();

  if (!bfd_section_already_linked_table_init ())
    einfo (_("%P%F: Failed to create hash table\n"));

  /* Create a bfd for each input file.  */
  current_target = default_target;
  open_input_bfds (statement_list.head, FALSE);

  link_info.gc_sym_list = &entry_symbol;
  if (entry_symbol.name == NULL)
    link_info.gc_sym_list = ldlang_undef_chain_list_head;

  ldemul_after_open ();

  bfd_section_already_linked_table_free ();

  /* Make sure that we're not mixing architectures.  We call this
     after all the input files have been opened, but before we do any
     other processing, so that any operations merge_private_bfd_data
     does on the output file will be known during the rest of the
     link.  */
  lang_check ();

  /* Handle .exports instead of a version script if we're told to do so.  */
  if (command_line.version_exports_section)
    lang_do_version_exports_section ();

  /* Build all sets based on the information gathered from the input
     files.  */
  ldctor_build_sets ();

  /* Remove unreferenced sections if asked to.  */
  lang_gc_sections ();

  /* Size up the common data.  */
  lang_common ();

  /* Update wild statements.  */
  update_wild_statements (statement_list.head);

  /* Run through the contours of the script and attach input sections
     to the correct output sections.  */
  map_input_to_output_sections (statement_list.head, NULL, NULL);

  /* Find any sections not attached explicitly and handle them.  */
  lang_place_orphans ();

  if (! link_info.relocatable)
    {
      asection *found;

      /* Merge SEC_MERGE sections.  This has to be done after GC of
	 sections, so that GCed sections are not merged, but before
	 assigning dynamic symbols, since removing whole input sections
	 is hard then.  */
      bfd_merge_sections (output_bfd, &link_info);

      /* Look for a text section and set the readonly attribute in it.  */
      found = bfd_get_section_by_name (output_bfd, ".text");

      if (found != NULL)
	{
	  if (config.text_read_only)
	    found->flags |= SEC_READONLY;
	  else
	    found->flags &= ~SEC_READONLY;
	}
    }

  /* Do anything special before sizing sections.  This is where ELF
     and other back-ends size dynamic sections.  */
  ldemul_before_allocation ();

  /* We must record the program headers before we try to fix the
     section positions, since they will affect SIZEOF_HEADERS.  */
  lang_record_phdrs ();

  /* Size up the sections.  */
  lang_size_sections (NULL, !command_line.relax);

  /* Now run around and relax if we can.  */
  if (command_line.relax)
    {
      /* We may need more than one relaxation pass.  */
      int i = link_info.relax_pass;

      /* The backend can use it to determine the current pass.  */
      link_info.relax_pass = 0;

      while (i--)
	{
	  relax_sections ();
	  link_info.relax_pass++;
	}

      /* Final extra sizing to report errors.  */
      lang_do_assignments ();
      lang_reset_memory_regions ();
      lang_size_sections (NULL, TRUE);
    }

  /* See if anything special should be done now we know how big
     everything is.  */
  ldemul_after_allocation ();

  /* Fix any .startof. or .sizeof. symbols.  */
  lang_set_startof ();

  /* Do all the assignments, now that we know the final resting places
     of all the symbols.  */

  lang_do_assignments ();

  ldemul_finish ();

  /* Make sure that the section addresses make sense.  */
  if (! link_info.relocatable
      && command_line.check_section_addresses)
    lang_check_section_addresses ();

  lang_end ();
}