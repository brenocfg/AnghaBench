#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_5__ {int flags; unsigned int reloc_count; int /*<<< orphan*/ * relocation; TYPE_2__* constructor_chain; } ;
typedef  TYPE_1__ asection ;
struct TYPE_6__ {int /*<<< orphan*/  relent; struct TYPE_6__* next; } ;
typedef  TYPE_2__ arelent_chain ;
typedef  int /*<<< orphan*/  arelent ;

/* Variables and functions */
 int SEC_CONSTRUCTOR ; 
 int /*<<< orphan*/  ecoff_slurp_reloc_table (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 

long
_bfd_ecoff_canonicalize_reloc (bfd *abfd,
			       asection *section,
			       arelent **relptr,
			       asymbol **symbols)
{
  unsigned int count;

  if (section->flags & SEC_CONSTRUCTOR)
    {
      arelent_chain *chain;

      /* This section has relocs made up by us, not the file, so take
	 them out of their chain and place them into the data area
	 provided.  */
      for (count = 0, chain = section->constructor_chain;
	   count < section->reloc_count;
	   count++, chain = chain->next)
	*relptr++ = &chain->relent;
    }
  else
    {
      arelent *tblptr;

      if (! ecoff_slurp_reloc_table (abfd, section, symbols))
	return -1;

      tblptr = section->relocation;

      for (count = 0; count < section->reloc_count; count++)
	*relptr++ = tblptr++;
    }

  *relptr = NULL;

  return section->reloc_count;
}