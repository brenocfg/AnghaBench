#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
typedef  size_t relax_substateT ;
typedef  scalar_t__ offsetT ;
struct TYPE_4__ {int /*<<< orphan*/ * fr_symbol; } ;
typedef  TYPE_1__ fragS ;
struct TYPE_5__ {scalar_t__ rlx_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 TYPE_3__* md_relax_table ; 

void
mep_prepare_relax_scan (fragS *fragP, offsetT *aim, relax_substateT this_state)
{
  symbolS *symbolP = fragP->fr_symbol;
  if (symbolP && !S_IS_DEFINED (symbolP))
    *aim = 0;
  /* Adjust for MeP pcrel not being relative to the next opcode.  */
  *aim += 2 + md_relax_table[this_state].rlx_length;
}