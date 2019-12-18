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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_5__ {int address; int addend; TYPE_2__* howto; } ;
typedef  TYPE_1__ arelent ;
struct TYPE_6__ {int size; } ;

/* Variables and functions */
 TYPE_2__* howto_align_table ; 
 TYPE_2__* howto_done_align_table ; 
 int output_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perform_slip (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
aligncode (bfd *abfd,
	   asection *input_section,
	   arelent *r,
	   unsigned int shrink)
{
  bfd_vma dot = output_addr (input_section) + r->address;
  bfd_vma gap;
  bfd_vma old_end;
  bfd_vma new_end;
  unsigned int shrink_delta;
  int size = r->howto->size;

  /* Reduce the size of the alignment so that it's still aligned but
     smaller  - the current size is already the same size as or bigger
     than the alignment required.  */

  /* Calculate the first byte following the padding before we optimize.  */
  old_end = ((dot + size ) & ~size) + size+1;
  /* Work out where the new end will be - remember that we're smaller
     than we used to be.  */
  new_end = ((dot - shrink + size) & ~size);

  /* This is the new end.  */
  gap = old_end - ((dot + size) & ~size);

  shrink_delta = (old_end - new_end) - shrink;

  if (shrink_delta)
    {
      /* Change the reloc so that it knows how far to align to.  */
      r->howto = howto_done_align_table + (r->howto - howto_align_table);

      /* Encode the stuff into the addend - for future use we need to
	 know how big the reloc used to be.  */
      r->addend = old_end - dot + r->address;

      /* This will be N bytes smaller in the long run, adjust all the symbols.  */
      perform_slip (abfd, shrink_delta, input_section, r->address - shrink);
      shrink += shrink_delta;
    }

  return shrink;
}