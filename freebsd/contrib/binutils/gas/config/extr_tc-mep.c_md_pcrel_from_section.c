#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
typedef  scalar_t__ segT ;
struct TYPE_5__ {long fx_where; TYPE_1__* fx_frag; int /*<<< orphan*/ * fx_addsy; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_4__ {long fr_address; } ;

/* Variables and functions */
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_DEFINED (int /*<<< orphan*/ *) ; 

long
md_pcrel_from_section (fixS *fixP, segT sec)
{
  if (fixP->fx_addsy != (symbolS *) NULL
      && (! S_IS_DEFINED (fixP->fx_addsy)
	  || S_GET_SEGMENT (fixP->fx_addsy) != sec))
    /* The symbol is undefined (or is defined but not in this section).
       Let the linker figure it out.  */
    return 0;

  /* Return the address of the opcode - cgen adjusts for opcode size
     itself, to be consistent with the disassembler, which must do
     so.  */
  return fixP->fx_where + fixP->fx_frag->fr_address;
}