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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  BLKmode ; 
 int /*<<< orphan*/  GEN_INT (unsigned int) ; 
 unsigned int MEM_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QImode ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 scalar_t__ TARGET_BIG_ENDIAN ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_mem_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mips_get_unaligned_mem (rtx *op, unsigned int width, int bitpos,
			rtx *left, rtx *right)
{
  rtx first, last;

  /* Check that the operand really is a MEM.  Not all the extv and
     extzv predicates are checked.  */
  if (!MEM_P (*op))
    return false;

  /* Check that the size is valid.  */
  if (width != 32 && (!TARGET_64BIT || width != 64))
    return false;

  /* We can only access byte-aligned values.  Since we are always passed
     a reference to the first byte of the field, it is not necessary to
     do anything with BITPOS after this check.  */
  if (bitpos % BITS_PER_UNIT != 0)
    return false;

  /* Reject aligned bitfields: we want to use a normal load or store
     instead of a left/right pair.  */
  if (MEM_ALIGN (*op) >= width)
    return false;

  /* Adjust *OP to refer to the whole field.  This also has the effect
     of legitimizing *OP's address for BLKmode, possibly simplifying it.  */
  *op = adjust_address (*op, BLKmode, 0);
  set_mem_size (*op, GEN_INT (width / BITS_PER_UNIT));

  /* Get references to both ends of the field.  We deliberately don't
     use the original QImode *OP for FIRST since the new BLKmode one
     might have a simpler address.  */
  first = adjust_address (*op, QImode, 0);
  last = adjust_address (*op, QImode, width / BITS_PER_UNIT - 1);

  /* Allocate to LEFT and RIGHT according to endianness.  LEFT should
     be the upper word and RIGHT the lower word.  */
  if (TARGET_BIG_ENDIAN)
    *left = first, *right = last;
  else
    *left = last, *right = first;

  return true;
}