#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ symindex ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ carsym ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ BFD_NO_MORE_SYMBOLS ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 int /*<<< orphan*/ * bfd_get_elt_at_index (int /*<<< orphan*/ *,scalar_t__) ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_next_mapent (int /*<<< orphan*/ *,scalar_t__,TYPE_1__**) ; 
 int /*<<< orphan*/  print_symname (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_symdef_entry (bfd *abfd)
{
  symindex idx = BFD_NO_MORE_SYMBOLS;
  carsym *thesym;
  bfd_boolean everprinted = FALSE;

  for (idx = bfd_get_next_mapent (abfd, idx, &thesym);
       idx != BFD_NO_MORE_SYMBOLS;
       idx = bfd_get_next_mapent (abfd, idx, &thesym))
    {
      bfd *elt;
      if (!everprinted)
	{
	  printf (_("\nArchive index:\n"));
	  everprinted = TRUE;
	}
      elt = bfd_get_elt_at_index (abfd, idx);
      if (elt == NULL)
	bfd_fatal ("bfd_get_elt_at_index");
      if (thesym->name != (char *) NULL)
	{
	  print_symname ("%s", thesym->name, abfd);
	  printf (" in %s\n", bfd_get_filename (elt));
	}
    }
}