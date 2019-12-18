#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  bfd_core ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/ * bfd_make_section_anyway (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * bfd_openw (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_set_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_gcore_arch () ; 
 int /*<<< orphan*/  default_gcore_mach () ; 
 int /*<<< orphan*/  default_gcore_target () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ gcore_memory_sections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ info_verbose ; 
 struct cleanup* make_cleanup_bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noprocess () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  target_has_execution ; 
 void* target_make_corefile_notes (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gcore_command (char *args, int from_tty)
{
  struct cleanup *old_chain;
  char *corefilename, corefilename_buffer[40];
  asection *note_sec = NULL;
  bfd *obfd;
  void *note_data = NULL;
  int note_size = 0;

  /* No use generating a corefile without a target process.  */
  if (!target_has_execution)
    noprocess ();

  if (args && *args)
    corefilename = args;
  else
    {
      /* Default corefile name is "core.PID".  */
      sprintf (corefilename_buffer, "core.%d", PIDGET (inferior_ptid));
      corefilename = corefilename_buffer;
    }

  if (info_verbose)
    fprintf_filtered (gdb_stdout,
		      "Opening corefile '%s' for output.\n", corefilename);

  /* Open the output file.  */
  obfd = bfd_openw (corefilename, default_gcore_target ());
  if (!obfd)
    error ("Failed to open '%s' for output.", corefilename);

  /* Need a cleanup that will close the file (FIXME: delete it?).  */
  old_chain = make_cleanup_bfd_close (obfd);

  bfd_set_format (obfd, bfd_core);
  bfd_set_arch_mach (obfd, default_gcore_arch (), default_gcore_mach ());

  /* An external target method must build the notes section.  */
  note_data = target_make_corefile_notes (obfd, &note_size);

  /* Create the note section.  */
  if (note_data != NULL && note_size != 0)
    {
      note_sec = bfd_make_section_anyway (obfd, "note0");
      if (note_sec == NULL)
	error ("Failed to create 'note' section for corefile: %s",
	       bfd_errmsg (bfd_get_error ()));

      bfd_set_section_vma (obfd, note_sec, 0);
      bfd_set_section_flags (obfd, note_sec,
			     SEC_HAS_CONTENTS | SEC_READONLY | SEC_ALLOC);
      bfd_set_section_alignment (obfd, note_sec, 0);
      bfd_set_section_size (obfd, note_sec, note_size);
    }

  /* Now create the memory/load sections.  */
  if (gcore_memory_sections (obfd) == 0)
    error ("gcore: failed to get corefile memory sections from target.");

  /* Write out the contents of the note section.  */
  if (note_data != NULL && note_size != 0)
    {
      if (!bfd_set_section_contents (obfd, note_sec, note_data, 0, note_size))
	warning ("writing note section (%s)", bfd_errmsg (bfd_get_error ()));
    }

  /* Succeeded.  */
  fprintf_filtered (gdb_stdout, "Saved corefile %s\n", corefilename);

  /* Clean-ups will close the output file and free malloc memory.  */
  do_cleanups (old_chain);
  return;
}