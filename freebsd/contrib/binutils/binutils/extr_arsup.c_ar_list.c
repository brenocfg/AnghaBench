#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* archive_next; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_7__ {TYPE_1__* archive_head; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  ar_directory_doer (TYPE_1__*,TYPE_1__*) ; 
 char* bfd_get_filename (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  maybequit () ; 
 TYPE_2__* obfd ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int verbose ; 

void
ar_list (void)
{
  if (!obfd)
    {
      fprintf (stderr, _("%s: no open output archive\n"), program_name);
      maybequit ();
    }
  else
    {
      bfd *abfd;

      outfile = stdout;
      verbose =1 ;
      printf (_("Current open archive is %s\n"), bfd_get_filename (obfd));

      for (abfd = obfd->archive_head;
	   abfd != (bfd *)NULL;
	   abfd = abfd->archive_next)
	ar_directory_doer (abfd, (bfd *) NULL);
    }
}