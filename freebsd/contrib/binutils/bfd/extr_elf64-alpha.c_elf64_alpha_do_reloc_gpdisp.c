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
typedef  int bfd_vma ;
typedef  scalar_t__ bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 unsigned long bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_reloc_dangerous ; 
 int /*<<< orphan*/  bfd_reloc_ok ; 
 int /*<<< orphan*/  bfd_reloc_overflow ; 

__attribute__((used)) static bfd_reloc_status_type
elf64_alpha_do_reloc_gpdisp (bfd *abfd, bfd_vma gpdisp, bfd_byte *p_ldah,
			     bfd_byte *p_lda)
{
  bfd_reloc_status_type ret = bfd_reloc_ok;
  bfd_vma addend;
  unsigned long i_ldah, i_lda;

  i_ldah = bfd_get_32 (abfd, p_ldah);
  i_lda = bfd_get_32 (abfd, p_lda);

  /* Complain if the instructions are not correct.  */
  if (((i_ldah >> 26) & 0x3f) != 0x09
      || ((i_lda >> 26) & 0x3f) != 0x08)
    ret = bfd_reloc_dangerous;

  /* Extract the user-supplied offset, mirroring the sign extensions
     that the instructions perform.  */
  addend = ((i_ldah & 0xffff) << 16) | (i_lda & 0xffff);
  addend = (addend ^ 0x80008000) - 0x80008000;

  gpdisp += addend;

  if ((bfd_signed_vma) gpdisp < -(bfd_signed_vma) 0x80000000
      || (bfd_signed_vma) gpdisp >= (bfd_signed_vma) 0x7fff8000)
    ret = bfd_reloc_overflow;

  /* compensate for the sign extension again.  */
  i_ldah = ((i_ldah & 0xffff0000)
	    | (((gpdisp >> 16) + ((gpdisp >> 15) & 1)) & 0xffff));
  i_lda = (i_lda & 0xffff0000) | (gpdisp & 0xffff);

  bfd_put_32 (abfd, (bfd_vma) i_ldah, p_ldah);
  bfd_put_32 (abfd, (bfd_vma) i_lda, p_lda);

  return ret;
}