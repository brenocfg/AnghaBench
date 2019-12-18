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
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  arelent ;

/* Variables and functions */
 long bfd_canonicalize_dynamic_reloc (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 long bfd_get_dynamic_reloc_upper_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_reloc_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,long) ; 
 int /*<<< orphan*/  dynsyms ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ ** xmalloc (long) ; 

__attribute__((used)) static void
dump_dynamic_relocs (bfd *abfd)
{
  long relsize;
  arelent **relpp;
  long relcount;

  relsize = bfd_get_dynamic_reloc_upper_bound (abfd);
  if (relsize < 0)
    bfd_fatal (bfd_get_filename (abfd));

  printf ("DYNAMIC RELOCATION RECORDS");

  if (relsize == 0)
    printf (" (none)\n\n");
  else
    {
      relpp = xmalloc (relsize);
      relcount = bfd_canonicalize_dynamic_reloc (abfd, relpp, dynsyms);

      if (relcount < 0)
	bfd_fatal (bfd_get_filename (abfd));
      else if (relcount == 0)
	printf (" (none)\n\n");
      else
	{
	  printf ("\n");
	  dump_reloc_set (abfd, NULL, relpp, relcount);
	  printf ("\n\n");
	}
      free (relpp);
    }
}