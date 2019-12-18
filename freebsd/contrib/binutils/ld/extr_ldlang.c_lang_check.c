#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * the_bfd; TYPE_2__* next; } ;
struct TYPE_7__ {TYPE_1__ input_statement; } ;
typedef  TYPE_2__ lang_statement_union_type ;
typedef  int /*<<< orphan*/ * bfd_error_handler_type ;
typedef  int /*<<< orphan*/  bfd_arch_info_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_10__ {scalar_t__ warn_mismatch; int /*<<< orphan*/  accept_unknown_input_arch; } ;
struct TYPE_9__ {TYPE_2__* head; } ;
struct TYPE_8__ {scalar_t__ emitrelocations; scalar_t__ relocatable; } ;

/* Variables and functions */
 int HAS_RELOC ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * bfd_arch_get_compatible (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_count_sections (int /*<<< orphan*/ *) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_merge_private_bfd_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_printable_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_set_error_handler (int /*<<< orphan*/ *) ; 
 TYPE_5__ command_line ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 TYPE_4__ file_chain ; 
 int /*<<< orphan*/ * ignore_bfd_errors ; 
 TYPE_3__ link_info ; 
 int /*<<< orphan*/ * output_bfd ; 

__attribute__((used)) static void
lang_check (void)
{
  lang_statement_union_type *file;
  bfd *input_bfd;
  const bfd_arch_info_type *compatible;

  for (file = file_chain.head; file != NULL; file = file->input_statement.next)
    {
      input_bfd = file->input_statement.the_bfd;
      compatible
	= bfd_arch_get_compatible (input_bfd, output_bfd,
				   command_line.accept_unknown_input_arch);

      /* In general it is not possible to perform a relocatable
	 link between differing object formats when the input
	 file has relocations, because the relocations in the
	 input format may not have equivalent representations in
	 the output format (and besides BFD does not translate
	 relocs for other link purposes than a final link).  */
      if ((link_info.relocatable || link_info.emitrelocations)
	  && (compatible == NULL
	      || bfd_get_flavour (input_bfd) != bfd_get_flavour (output_bfd))
	  && (bfd_get_file_flags (input_bfd) & HAS_RELOC) != 0)
	{
	  einfo (_("%P%F: Relocatable linking with relocations from"
		   " format %s (%B) to format %s (%B) is not supported\n"),
		 bfd_get_target (input_bfd), input_bfd,
		 bfd_get_target (output_bfd), output_bfd);
	  /* einfo with %F exits.  */
	}

      if (compatible == NULL)
	{
	  if (command_line.warn_mismatch)
	    einfo (_("%P%X: %s architecture of input file `%B'"
		     " is incompatible with %s output\n"),
		   bfd_printable_name (input_bfd), input_bfd,
		   bfd_printable_name (output_bfd));
	}
      else if (bfd_count_sections (input_bfd))
	{
	  /* If the input bfd has no contents, it shouldn't set the
	     private data of the output bfd.  */

	  bfd_error_handler_type pfn = NULL;

	  /* If we aren't supposed to warn about mismatched input
	     files, temporarily set the BFD error handler to a
	     function which will do nothing.  We still want to call
	     bfd_merge_private_bfd_data, since it may set up
	     information which is needed in the output file.  */
	  if (! command_line.warn_mismatch)
	    pfn = bfd_set_error_handler (ignore_bfd_errors);
	  if (! bfd_merge_private_bfd_data (input_bfd, output_bfd))
	    {
	      if (command_line.warn_mismatch)
		einfo (_("%P%X: failed to merge target specific data"
			 " of file %B\n"), input_bfd);
	    }
	  if (! command_line.warn_mismatch)
	    bfd_set_error_handler (pfn);
	}
    }
}