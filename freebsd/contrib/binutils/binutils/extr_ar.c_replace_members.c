#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_mtime; } ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_10__ {char* filename; struct TYPE_10__* archive_next; int /*<<< orphan*/ * arelt_data; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ FALSE ; 
 scalar_t__ FILENAME_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ ar_emul_append (TYPE_1__**,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ar_emul_replace (TYPE_1__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 scalar_t__ bfd_stat_arch_elt (TYPE_1__*,struct stat*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__** get_pos_bfd (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ newer_only ; 
 int /*<<< orphan*/  normalize (char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * output_filename ; 
 int /*<<< orphan*/  pos_after ; 
 int /*<<< orphan*/  pos_end ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  write_archive (TYPE_1__*) ; 

__attribute__((used)) static void
replace_members (bfd *arch, char **files_to_move, bfd_boolean quick)
{
  bfd_boolean changed = FALSE;
  bfd **after_bfd;		/* New entries go after this one.  */
  bfd *current;
  bfd **current_ptr;

  while (files_to_move && *files_to_move)
    {
      if (! quick)
	{
	  current_ptr = &arch->archive_next;
	  while (*current_ptr)
	    {
	      current = *current_ptr;

	      /* For compatibility with existing ar programs, we
		 permit the same file to be added multiple times.  */
	      if (FILENAME_CMP (normalize (*files_to_move, arch),
				normalize (current->filename, arch)) == 0
		  && current->arelt_data != NULL)
		{
		  if (newer_only)
		    {
		      struct stat fsbuf, asbuf;

		      if (stat (*files_to_move, &fsbuf) != 0)
			{
			  if (errno != ENOENT)
			    bfd_fatal (*files_to_move);
			  goto next_file;
			}
		      if (bfd_stat_arch_elt (current, &asbuf) != 0)
			/* xgettext:c-format */
			fatal (_("internal stat error on %s"),
			       current->filename);

		      if (fsbuf.st_mtime <= asbuf.st_mtime)
			goto next_file;
		    }

		  after_bfd = get_pos_bfd (&arch->archive_next, pos_after,
					   current->filename);
		  if (ar_emul_replace (after_bfd, *files_to_move,
				       verbose))
		    {
		      /* Snip out this entry from the chain.  */
		      *current_ptr = (*current_ptr)->archive_next;
		      changed = TRUE;
		    }

		  goto next_file;
		}
	      current_ptr = &(current->archive_next);
	    }
	}

      /* Add to the end of the archive.  */
      after_bfd = get_pos_bfd (&arch->archive_next, pos_end, NULL);

      if (ar_emul_append (after_bfd, *files_to_move, verbose))
	changed = TRUE;

    next_file:;

      files_to_move++;
    }

  if (changed)
    write_archive (arch);
  else
    output_filename = NULL;
}