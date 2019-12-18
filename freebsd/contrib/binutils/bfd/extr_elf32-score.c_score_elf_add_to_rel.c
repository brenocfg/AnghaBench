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
struct TYPE_3__ {unsigned long type; int src_mask; unsigned long dst_mask; } ;
typedef  TYPE_1__ reloc_howto_type ;
typedef  int bfd_vma ;
typedef  int bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
#define  R_SCORE16_11 133 
#define  R_SCORE16_PC8 132 
#define  R_SCORE_24 131 
#define  R_SCORE_HI16 130 
#define  R_SCORE_LO16 129 
#define  R_SCORE_PC19 128 
 int bfd_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
score_elf_add_to_rel (bfd *abfd,
		      bfd_byte *address,
		      reloc_howto_type *howto,
		      bfd_signed_vma increment)
{
  bfd_signed_vma addend;
  bfd_vma contents;
  unsigned long offset;
  unsigned long r_type = howto->type;
  unsigned long hi16_addend, hi16_offset, hi16_value, uvalue;

  contents = bfd_get_32 (abfd, address);
  /* Get the (signed) value from the instruction.  */
  addend = contents & howto->src_mask;
  if (addend & ((howto->src_mask + 1) >> 1))
    {
      bfd_signed_vma mask;

      mask = -1;
      mask &= ~howto->src_mask;
      addend |= mask;
    }
  /* Add in the increment, (which is a byte value).  */
  switch (r_type)
    {
    case R_SCORE_PC19:
      offset =
        (((contents & howto->src_mask) & 0x3ff0000) >> 6) | ((contents & howto->src_mask) & 0x3ff);
      offset += increment;
      contents =
        (contents & ~howto->
         src_mask) | (((offset << 6) & howto->src_mask) & 0x3ff0000) | (offset & 0x3ff);
      bfd_put_32 (abfd, contents, address);
      break;
    case R_SCORE_HI16:
      break;
    case R_SCORE_LO16:
      hi16_addend = bfd_get_32 (abfd, address - 4);
      hi16_offset = ((((hi16_addend >> 16) & 0x3) << 15) | (hi16_addend & 0x7fff)) >> 1;
      offset = ((((contents >> 16) & 0x3) << 15) | (contents & 0x7fff)) >> 1;
      offset = (hi16_offset << 16) | (offset & 0xffff);
      uvalue = increment + offset;
      hi16_offset = (uvalue >> 16) << 1;
      hi16_value = (hi16_addend & (~(howto->dst_mask)))
        | (hi16_offset & 0x7fff) | ((hi16_offset << 1) & 0x30000);
      bfd_put_32 (abfd, hi16_value, address - 4);
      offset = (uvalue & 0xffff) << 1;
      contents = (contents & (~(howto->dst_mask))) | (offset & 0x7fff) | ((offset << 1) & 0x30000);
      bfd_put_32 (abfd, contents, address);
      break;
    case R_SCORE_24:
      offset =
        (((contents & howto->src_mask) >> 1) & 0x1ff8000) | ((contents & howto->src_mask) & 0x7fff);
      offset += increment;
      contents =
        (contents & ~howto->
         src_mask) | (((offset << 1) & howto->src_mask) & 0x3ff0000) | (offset & 0x7fff);
      bfd_put_32 (abfd, contents, address);
      break;
    case R_SCORE16_11:

      contents = bfd_get_16 (abfd, address);
      offset = contents & howto->src_mask;
      offset += increment;
      contents = (contents & ~howto->src_mask) | (offset & howto->src_mask);
      bfd_put_16 (abfd, contents, address);

      break;
    case R_SCORE16_PC8:

      contents = bfd_get_16 (abfd, address);
      offset = (contents & howto->src_mask) + ((increment >> 1) & 0xff);
      contents = (contents & (~howto->src_mask)) | (offset & howto->src_mask);
      bfd_put_16 (abfd, contents, address);

      break;
    default:
      addend += increment;
      contents = (contents & ~howto->dst_mask) | (addend & howto->dst_mask);
      bfd_put_32 (abfd, contents, address);
      break;
    }
}