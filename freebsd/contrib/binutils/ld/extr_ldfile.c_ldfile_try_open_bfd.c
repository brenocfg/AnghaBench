#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__* the_bfd; int /*<<< orphan*/  local_sym_name; scalar_t__ search_dirs_flag; int /*<<< orphan*/  dynamic; int /*<<< orphan*/  target; } ;
typedef  TYPE_2__ lang_input_statement_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_19__ {int flags; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_21__ {scalar_t__ warn_search_mismatch; int /*<<< orphan*/  accept_unknown_input_arch; int /*<<< orphan*/  endian; } ;
struct TYPE_17__ {char* str; } ;
struct TYPE_20__ {char* name; TYPE_1__ bigint; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DYNAMIC ; 
#define  ENDIAN_BIG 136 
#define  ENDIAN_LITTLE 135 
#define  ENDIAN_UNSET 134 
 int /*<<< orphan*/  FALSE ; 
 int INPUT_SCRIPT ; 
#define  INT 133 
#define  LNAME 132 
#define  NAME 131 
#define  OUTPUT_FORMAT 130 
 int /*<<< orphan*/  TRUE ; 
#define  VERS_IDENTIFIER 129 
#define  VERS_TAG 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_arch_get_compatible (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (TYPE_3__*) ; 
 scalar_t__ bfd_error_file_not_recognized ; 
 scalar_t__ bfd_error_invalid_target ; 
 scalar_t__ bfd_get_error () ; 
 scalar_t__ bfd_get_flavour (TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_object ; 
 TYPE_3__* bfd_openr (char const*,int /*<<< orphan*/ ) ; 
 TYPE_3__* bfd_openr_next_archived_file (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_xcoff_flavour ; 
 TYPE_8__ command_line ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  info_msg (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  input_selected ; 
 int /*<<< orphan*/  lang_get_output_target () ; 
 int /*<<< orphan*/  ldemul_unrecognized_file (TYPE_2__*) ; 
 int /*<<< orphan*/  ldfile_assumed_script ; 
 int /*<<< orphan*/  ldfile_open_command_file (char const*) ; 
 int /*<<< orphan*/  ldlex_both () ; 
 int /*<<< orphan*/  ldlex_popstate () ; 
 TYPE_3__* output_bfd ; 
 int /*<<< orphan*/  parser_input ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ trace_file_tries ; 
 int yylex () ; 
 TYPE_4__ yylval ; 

bfd_boolean
ldfile_try_open_bfd (const char *attempt,
		     lang_input_statement_type *entry)
{
  entry->the_bfd = bfd_openr (attempt, entry->target);

  if (trace_file_tries)
    {
      if (entry->the_bfd == NULL)
	info_msg (_("attempt to open %s failed\n"), attempt);
      else
	info_msg (_("attempt to open %s succeeded\n"), attempt);
    }

  if (entry->the_bfd == NULL)
    {
      if (bfd_get_error () == bfd_error_invalid_target)
	einfo (_("%F%P: invalid BFD target `%s'\n"), entry->target);
      return FALSE;
    }

  /* If we are searching for this file, see if the architecture is
     compatible with the output file.  If it isn't, keep searching.
     If we can't open the file as an object file, stop the search
     here.  If we are statically linking, ensure that we don't link
     a dynamic object.  */

  if (entry->search_dirs_flag || !entry->dynamic)
    {
      bfd *check;

      if (bfd_check_format (entry->the_bfd, bfd_archive))
	check = bfd_openr_next_archived_file (entry->the_bfd, NULL);
      else
	check = entry->the_bfd;

      if (check != NULL)
	{
	  if (! bfd_check_format (check, bfd_object))
	    {
	      if (check == entry->the_bfd
		  && entry->search_dirs_flag
		  && bfd_get_error () == bfd_error_file_not_recognized
		  && ! ldemul_unrecognized_file (entry))
		{
		  int token, skip = 0;
		  char *arg, *arg1, *arg2, *arg3;
		  extern FILE *yyin;

		  /* Try to interpret the file as a linker script.  */
		  ldfile_open_command_file (attempt);

		  ldfile_assumed_script = TRUE;
		  parser_input = input_selected;
		  ldlex_both ();
		  token = INPUT_SCRIPT;
		  while (token != 0)
		    {
		      switch (token)
			{
			case OUTPUT_FORMAT:
			  if ((token = yylex ()) != '(')
			    continue;
			  if ((token = yylex ()) != NAME)
			    continue;
			  arg1 = yylval.name;
			  arg2 = NULL;
			  arg3 = NULL;
			  token = yylex ();
			  if (token == ',')
			    {
			      if ((token = yylex ()) != NAME)
				{
				  free (arg1);
				  continue;
				}
			      arg2 = yylval.name;
			      if ((token = yylex ()) != ','
				  || (token = yylex ()) != NAME)
				{
				  free (arg1);
				  free (arg2);
				  continue;
				}
			      arg3 = yylval.name;
			      token = yylex ();
			    }
			  if (token == ')')
			    {
			      switch (command_line.endian)
				{
				default:
				case ENDIAN_UNSET:
				  arg = arg1; break;
				case ENDIAN_BIG:
				  arg = arg2 ? arg2 : arg1; break;
				case ENDIAN_LITTLE:
				  arg = arg3 ? arg3 : arg1; break;
				}
			      if (strcmp (arg, lang_get_output_target ()) != 0)
				skip = 1;
			    }
			  free (arg1);
			  if (arg2) free (arg2);
			  if (arg3) free (arg3);
			  break;
			case NAME:
			case LNAME:
			case VERS_IDENTIFIER:
			case VERS_TAG:
			  free (yylval.name);
			  break;
			case INT:
			  if (yylval.bigint.str)
			    free (yylval.bigint.str);
			  break;
			}
		      token = yylex ();
		    }
		  ldlex_popstate ();
		  ldfile_assumed_script = FALSE;
		  fclose (yyin);
		  yyin = NULL;
		  if (skip)
		    {
		      if (command_line.warn_search_mismatch)
			einfo (_("%P: skipping incompatible %s "
				 "when searching for %s\n"),
			       attempt, entry->local_sym_name);
		      bfd_close (entry->the_bfd);
		      entry->the_bfd = NULL;
		      return FALSE;
		    }
		}
	      return TRUE;
	    }

	  if (!entry->dynamic && (entry->the_bfd->flags & DYNAMIC) != 0)
	    {
	      einfo (_("%F%P: attempted static link of dynamic object `%s'\n"),
		     attempt);
	      bfd_close (entry->the_bfd);
	      entry->the_bfd = NULL;
	      return FALSE;
	    }

	  if (entry->search_dirs_flag
	      && !bfd_arch_get_compatible (check, output_bfd,
					   command_line.accept_unknown_input_arch)
	      /* XCOFF archives can have 32 and 64 bit objects.  */
	      && ! (bfd_get_flavour (check) == bfd_target_xcoff_flavour
		    && bfd_get_flavour (output_bfd) == bfd_target_xcoff_flavour
		    && bfd_check_format (entry->the_bfd, bfd_archive)))
	    {
	      if (command_line.warn_search_mismatch)
		einfo (_("%P: skipping incompatible %s "
			 "when searching for %s\n"),
		       attempt, entry->local_sym_name);
	      bfd_close (entry->the_bfd);
	      entry->the_bfd = NULL;
	      return FALSE;
	    }
	}
    }

  return TRUE;
}