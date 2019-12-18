#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * bsym; TYPE_1__* sy_frag; } ;
typedef  TYPE_2__ symbolS ;
typedef  int offsetT ;
struct TYPE_10__ {int fr_address; int insn_addr; int /*<<< orphan*/  fr_subtype; int /*<<< orphan*/ * fr_opcode; int /*<<< orphan*/  fr_literal; TYPE_2__* fr_symbol; } ;
typedef  TYPE_3__ fragS ;
typedef  int addressT ;
struct TYPE_8__ {scalar_t__ fr_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_SIZE ; 
 int RELAX_NEW (int /*<<< orphan*/ ) ; 
 int RELAX_OLD (int /*<<< orphan*/ ) ; 
 int RELAX_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELAX_OPT_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IS_COMMON (TYPE_2__*) ; 
 scalar_t__ S_IS_DEFINED (TYPE_2__*) ; 
 int /*<<< orphan*/  S_IS_EXTERNAL (TYPE_2__*) ; 
 unsigned long md_chars_to_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
b32_relax_to_b16 (fragS * fragp)
{
  int grows = 0;
  int relaxable_p = 0;
  int old;
  int new;
  int frag_addr = fragp->fr_address + fragp->insn_addr;

  addressT symbol_address = 0;
  symbolS *s;
  offsetT offset;
  unsigned long value;
  unsigned long abs_value;

  /* FIXME : here may be able to modify better .
     I don't know how to get the fragp's section ,
     so in relax stage , it may be wrong to calculate the symbol's offset when the frag's section
     is different from the symbol's.  */

  old = RELAX_OLD (fragp->fr_subtype);
  new = RELAX_NEW (fragp->fr_subtype);
  relaxable_p = RELAX_OPT (fragp->fr_subtype);

  s = fragp->fr_symbol;
  /* b/bl immediate  */
  if (s == NULL)
    frag_addr = 0;
  else
    {
      if (s->bsym != 0)
	symbol_address = (addressT) s->sy_frag->fr_address;
    }

  value = md_chars_to_number (fragp->fr_literal, INSN_SIZE);

  /* b 32's offset : 20 bit, b 16's tolerate field : 0xff.  */
  offset = ((value & 0x3ff0000) >> 6) | (value & 0x3fe);
  if ((offset & 0x80000) == 0x80000)
    offset |= 0xfff00000;

  abs_value = offset + symbol_address - frag_addr;
  if ((abs_value & 0x80000000) == 0x80000000)
    abs_value = 0xffffffff - abs_value + 1;

  /* Relax branch 32 to branch 16.  */
  if (relaxable_p && (s->bsym != NULL) && ((abs_value & 0xffffff00) == 0)
      && (S_IS_DEFINED (s) && !S_IS_COMMON (s) && !S_IS_EXTERNAL (s)))
    {
      /* do nothing.  */
    }
  else
    {
      /* Branch 32 can not be relaxed to b 16, so clear OPT bit.  */
      fragp->fr_opcode = NULL;
      fragp->fr_subtype = RELAX_OPT_CLEAR (fragp->fr_subtype);
    }

  return grows;
}