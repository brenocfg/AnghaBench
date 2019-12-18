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
typedef  TYPE_1__* sec_ptr ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  relent; } ;
typedef  TYPE_2__ arelent_chain ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_5__ {int flags; unsigned int reloc_count; int /*<<< orphan*/ * relocation; TYPE_2__* constructor_chain; } ;

/* Variables and functions */
 int SEC_CONSTRUCTOR ; 
 int /*<<< orphan*/  coff_slurp_reloc_table (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static long
coff_canonicalize_reloc (bfd * abfd,
			 sec_ptr section,
			 arelent ** relptr,
			 asymbol ** symbols)
{
  arelent *tblptr = section->relocation;
  unsigned int count = 0;

  if (section->flags & SEC_CONSTRUCTOR)
    {
      /* This section has relocs made up by us, they are not in the
	 file, so take them out of their chain and place them into
	 the data area provided.  */
      arelent_chain *chain = section->constructor_chain;

      for (count = 0; count < section->reloc_count; count++)
	{
	  *relptr++ = &chain->relent;
	  chain = chain->next;
	}
    }
  else
    {
      if (! coff_slurp_reloc_table (abfd, section, symbols))
	return -1;

      tblptr = section->relocation;

      for (; count++ < section->reloc_count;)
	*relptr++ = tblptr++;
    }
  *relptr = 0;
  return section->reloc_count;
}