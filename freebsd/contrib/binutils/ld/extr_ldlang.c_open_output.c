#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum bfd_endian { ____Placeholder_bfd_endian } bfd_endian ;
struct TYPE_8__ {int byteorder; TYPE_1__* alternative_target; } ;
typedef  TYPE_2__ bfd_target ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_11__ {scalar_t__ endian; } ;
struct TYPE_10__ {int /*<<< orphan*/ * hash; } ;
struct TYPE_9__ {scalar_t__ name; } ;
struct TYPE_7__ {int byteorder; scalar_t__ name; } ;

/* Variables and functions */
 int BFD_ENDIAN_BIG ; 
 int BFD_ENDIAN_LITTLE ; 
 scalar_t__ ENDIAN_BIG ; 
 scalar_t__ ENDIAN_UNSET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ bfd_error_invalid_target ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/ * bfd_link_hash_table_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openw (char const*,scalar_t__) ; 
 TYPE_2__* bfd_search_for_target (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_gp_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closest_target_match ; 
 TYPE_5__ command_line ; 
 int /*<<< orphan*/  delete_output_file_on_failure ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  g_switch_value ; 
 int /*<<< orphan*/  get_target ; 
 scalar_t__ lang_get_output_target () ; 
 int /*<<< orphan*/  ldfile_output_architecture ; 
 int /*<<< orphan*/  ldfile_output_machine ; 
 TYPE_4__ link_info ; 
 scalar_t__ output_target ; 
 TYPE_3__* winner ; 

__attribute__((used)) static bfd *
open_output (const char *name)
{
  bfd *output;

  output_target = lang_get_output_target ();

  /* Has the user requested a particular endianness on the command
     line?  */
  if (command_line.endian != ENDIAN_UNSET)
    {
      const bfd_target *target;
      enum bfd_endian desired_endian;

      /* Get the chosen target.  */
      target = bfd_search_for_target (get_target, (void *) output_target);

      /* If the target is not supported, we cannot do anything.  */
      if (target != NULL)
	{
	  if (command_line.endian == ENDIAN_BIG)
	    desired_endian = BFD_ENDIAN_BIG;
	  else
	    desired_endian = BFD_ENDIAN_LITTLE;

	  /* See if the target has the wrong endianness.  This should
	     not happen if the linker script has provided big and
	     little endian alternatives, but some scrips don't do
	     this.  */
	  if (target->byteorder != desired_endian)
	    {
	      /* If it does, then see if the target provides
		 an alternative with the correct endianness.  */
	      if (target->alternative_target != NULL
		  && (target->alternative_target->byteorder == desired_endian))
		output_target = target->alternative_target->name;
	      else
		{
		  /* Try to find a target as similar as possible to
		     the default target, but which has the desired
		     endian characteristic.  */
		  bfd_search_for_target (closest_target_match,
					 (void *) target);

		  /* Oh dear - we could not find any targets that
		     satisfy our requirements.  */
		  if (winner == NULL)
		    einfo (_("%P: warning: could not find any targets"
			     " that match endianness requirement\n"));
		  else
		    output_target = winner->name;
		}
	    }
	}
    }

  output = bfd_openw (name, output_target);

  if (output == NULL)
    {
      if (bfd_get_error () == bfd_error_invalid_target)
	einfo (_("%P%F: target %s not found\n"), output_target);

      einfo (_("%P%F: cannot open output file %s: %E\n"), name);
    }

  delete_output_file_on_failure = TRUE;

  if (! bfd_set_format (output, bfd_object))
    einfo (_("%P%F:%s: can not make object file: %E\n"), name);
  if (! bfd_set_arch_mach (output,
			   ldfile_output_architecture,
			   ldfile_output_machine))
    einfo (_("%P%F:%s: can not set architecture: %E\n"), name);

  link_info.hash = bfd_link_hash_table_create (output);
  if (link_info.hash == NULL)
    einfo (_("%P%F: can not create hash table: %E\n"));

  bfd_set_gp_size (output, g_switch_value);
  return output;
}