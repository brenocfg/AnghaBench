#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  (* use_anchors_for_symbol_p ) (int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_ANCHOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SYMBOL_REF_BLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF_BLOCK_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_REF_HAS_BLOCK_INFO_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_REF_TLS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cse_not_expected ; 
 int /*<<< orphan*/  flag_section_anchors ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_section_anchor (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  place_block_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  replace_equiv_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__ targetm ; 

rtx
use_anchored_address (rtx x)
{
  rtx base;
  HOST_WIDE_INT offset;

  if (!flag_section_anchors)
    return x;

  if (!MEM_P (x))
    return x;

  /* Split the address into a base and offset.  */
  base = XEXP (x, 0);
  offset = 0;
  if (GET_CODE (base) == CONST
      && GET_CODE (XEXP (base, 0)) == PLUS
      && GET_CODE (XEXP (XEXP (base, 0), 1)) == CONST_INT)
    {
      offset += INTVAL (XEXP (XEXP (base, 0), 1));
      base = XEXP (XEXP (base, 0), 0);
    }

  /* Check whether BASE is suitable for anchors.  */
  if (GET_CODE (base) != SYMBOL_REF
      || !SYMBOL_REF_HAS_BLOCK_INFO_P (base)
      || SYMBOL_REF_ANCHOR_P (base)
      || SYMBOL_REF_BLOCK (base) == NULL
      || !targetm.use_anchors_for_symbol_p (base))
    return x;

  /* Decide where BASE is going to be.  */
  place_block_symbol (base);

  /* Get the anchor we need to use.  */
  offset += SYMBOL_REF_BLOCK_OFFSET (base);
  base = get_section_anchor (SYMBOL_REF_BLOCK (base), offset,
			     SYMBOL_REF_TLS_MODEL (base));

  /* Work out the offset from the anchor.  */
  offset -= SYMBOL_REF_BLOCK_OFFSET (base);

  /* If we're going to run a CSE pass, force the anchor into a register.
     We will then be able to reuse registers for several accesses, if the
     target costs say that that's worthwhile.  */
  if (!cse_not_expected)
    base = force_reg (GET_MODE (base), base);

  return replace_equiv_address (x, plus_constant (base, offset));
}