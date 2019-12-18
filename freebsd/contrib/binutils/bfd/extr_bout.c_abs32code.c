#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
typedef  unsigned int bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {int address; int /*<<< orphan*/ * howto; } ;
typedef  TYPE_1__ arelent ;

/* Variables and functions */
 unsigned int get_value (TYPE_1__*,struct bfd_link_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  howto_reloc_abs32codeshrunk ; 
 unsigned int output_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perform_slip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int
abs32code (bfd *abfd,
	   asection *input_section,
	   arelent *r,
	   unsigned int shrink,
	   struct bfd_link_info *link_info)
{
  bfd_vma value = get_value (r, link_info, input_section);
  bfd_vma dot = output_addr (input_section) + r->address;
  bfd_vma gap;

  /* See if the address we're looking at within 2^23 bytes of where
     we are, if so then we can use a small branch rather than the
     jump we were going to.  */
  gap = value - (dot - shrink);

  if (-1 << 23 < (long)gap && (long)gap < 1 << 23)
    {
      /* Change the reloc type from 32bitcode possible 24, to 24bit
	 possible 32.  */
      r->howto = &howto_reloc_abs32codeshrunk;
      /* The place to relc moves back by four bytes.  */
      r->address -=4;

      /* This will be four bytes smaller in the long run.  */
      shrink += 4 ;
      perform_slip (abfd, 4, input_section, r->address-shrink + 4);
    }

  return shrink;
}