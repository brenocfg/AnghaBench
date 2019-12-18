#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lang_statement_list_type ;
struct TYPE_15__ {int loaded; char* the_bfd; int sysrooted; int as_needed; int add_needed; int /*<<< orphan*/  whole_archive; int /*<<< orphan*/  dynamic; int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ lang_input_statement_type ;
typedef  scalar_t__ bfd_error_type ;
typedef  int bfd_boolean ;
typedef  char bfd ;
struct TYPE_16__ {TYPE_1__* callbacks; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* add_archive_element ) (TYPE_3__*,char*,char*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  dynamic_link; } ;

/* Variables and functions */
 void* FALSE ; 
 int TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int add_needed ; 
 int as_needed ; 
#define  bfd_archive 129 
 int /*<<< orphan*/  bfd_check_format (char*,int const) ; 
 int /*<<< orphan*/  bfd_check_format_matches (char*,int,char***) ; 
 int /*<<< orphan*/  bfd_close (char*) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 scalar_t__ bfd_error_file_not_recognized ; 
 scalar_t__ bfd_get_error () ; 
 int bfd_get_format (char*) ; 
 scalar_t__ bfd_link_add_symbols (char*,TYPE_3__*) ; 
#define  bfd_object 128 
 char* bfd_openr_next_archived_file (char*,char*) ; 
 int /*<<< orphan*/  check_excluded_libs (char*) ; 
 TYPE_11__ config ; 
 int /*<<< orphan*/  einfo (char*,...) ; 
 int /*<<< orphan*/  info_msg (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  input_script ; 
 scalar_t__ ldemul_recognized_file (TYPE_2__*) ; 
 scalar_t__ ldemul_unrecognized_file (TYPE_2__*) ; 
 int ldfile_assumed_script ; 
 int /*<<< orphan*/  ldfile_open_command_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldfile_open_file (TYPE_2__*) ; 
 int /*<<< orphan*/  ldlang_add_file (TYPE_2__*) ; 
 int ldlang_sysrooted_script ; 
 TYPE_3__ link_info ; 
 int /*<<< orphan*/  parser_input ; 
 int /*<<< orphan*/ * stat_ptr ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  trace_file_tries ; 
 int /*<<< orphan*/  trace_files ; 
 int /*<<< orphan*/  yyparse () ; 

bfd_boolean
load_symbols (lang_input_statement_type *entry,
	      lang_statement_list_type *place)
{
  char **matching;

  if (entry->loaded)
    return TRUE;

  ldfile_open_file (entry);

  if (! bfd_check_format (entry->the_bfd, bfd_archive)
      && ! bfd_check_format_matches (entry->the_bfd, bfd_object, &matching))
    {
      bfd_error_type err;
      lang_statement_list_type *hold;
      bfd_boolean bad_load = TRUE;
      bfd_boolean save_ldlang_sysrooted_script;
      bfd_boolean save_as_needed, save_add_needed;

      err = bfd_get_error ();

      /* See if the emulation has some special knowledge.  */
      if (ldemul_unrecognized_file (entry))
	return TRUE;

      if (err == bfd_error_file_ambiguously_recognized)
	{
	  char **p;

	  einfo (_("%B: file not recognized: %E\n"), entry->the_bfd);
	  einfo (_("%B: matching formats:"), entry->the_bfd);
	  for (p = matching; *p != NULL; p++)
	    einfo (" %s", *p);
	  einfo ("%F\n");
	}
      else if (err != bfd_error_file_not_recognized
	       || place == NULL)
	  einfo (_("%F%B: file not recognized: %E\n"), entry->the_bfd);
      else
	bad_load = FALSE;

      bfd_close (entry->the_bfd);
      entry->the_bfd = NULL;

      /* Try to interpret the file as a linker script.  */
      ldfile_open_command_file (entry->filename);

      hold = stat_ptr;
      stat_ptr = place;
      save_ldlang_sysrooted_script = ldlang_sysrooted_script;
      ldlang_sysrooted_script = entry->sysrooted;
      save_as_needed = as_needed;
      as_needed = entry->as_needed;
      save_add_needed = add_needed;
      add_needed = entry->add_needed;

      ldfile_assumed_script = TRUE;
      parser_input = input_script;
      /* We want to use the same -Bdynamic/-Bstatic as the one for
	 ENTRY.  */
      config.dynamic_link = entry->dynamic;
      yyparse ();
      ldfile_assumed_script = FALSE;

      ldlang_sysrooted_script = save_ldlang_sysrooted_script;
      as_needed = save_as_needed;
      add_needed = save_add_needed;
      stat_ptr = hold;

      return ! bad_load;
    }

  if (ldemul_recognized_file (entry))
    return TRUE;

  /* We don't call ldlang_add_file for an archive.  Instead, the
     add_symbols entry point will call ldlang_add_file, via the
     add_archive_element callback, for each element of the archive
     which is used.  */
  switch (bfd_get_format (entry->the_bfd))
    {
    default:
      break;

    case bfd_object:
      ldlang_add_file (entry);
      if (trace_files || trace_file_tries)
	info_msg ("%I\n", entry);
      break;

    case bfd_archive:
      check_excluded_libs (entry->the_bfd);

      if (entry->whole_archive)
	{
	  bfd *member = NULL;
	  bfd_boolean loaded = TRUE;

	  for (;;)
	    {
	      member = bfd_openr_next_archived_file (entry->the_bfd, member);

	      if (member == NULL)
		break;

	      if (! bfd_check_format (member, bfd_object))
		{
		  einfo (_("%F%B: member %B in archive is not an object\n"),
			 entry->the_bfd, member);
		  loaded = FALSE;
		}

	      if (! ((*link_info.callbacks->add_archive_element)
		     (&link_info, member, "--whole-archive")))
		abort ();

	      if (! bfd_link_add_symbols (member, &link_info))
		{
		  einfo (_("%F%B: could not read symbols: %E\n"), member);
		  loaded = FALSE;
		}
	    }

	  entry->loaded = loaded;
	  return loaded;
	}
      break;
    }

  if (bfd_link_add_symbols (entry->the_bfd, &link_info))
    entry->loaded = TRUE;
  else
    einfo (_("%F%B: could not read symbols: %E\n"), entry->the_bfd);

  return entry->loaded;
}