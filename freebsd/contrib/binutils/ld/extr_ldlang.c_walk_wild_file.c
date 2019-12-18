#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lang_wild_statement_type ;
struct TYPE_7__ {int /*<<< orphan*/ * the_bfd; } ;
typedef  TYPE_1__ lang_input_statement_type ;
typedef  int /*<<< orphan*/  callback_t ;
struct TYPE_8__ {TYPE_1__* usrdata; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_archive ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* bfd_openr_next_archived_file (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  walk_wild_section (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
walk_wild_file (lang_wild_statement_type *s,
		lang_input_statement_type *f,
		callback_t callback,
		void *data)
{
  if (f->the_bfd == NULL
      || ! bfd_check_format (f->the_bfd, bfd_archive))
    walk_wild_section (s, f, callback, data);
  else
    {
      bfd *member;

      /* This is an archive file.  We must map each member of the
	 archive separately.  */
      member = bfd_openr_next_archived_file (f->the_bfd, NULL);
      while (member != NULL)
	{
	  /* When lookup_name is called, it will call the add_symbols
	     entry point for the archive.  For each element of the
	     archive which is included, BFD will call ldlang_add_file,
	     which will set the usrdata field of the member to the
	     lang_input_statement.  */
	  if (member->usrdata != NULL)
	    {
	      walk_wild_section (s, member->usrdata, callback, data);
	    }

	  member = bfd_openr_next_archived_file (f->the_bfd, member);
	}
    }
}