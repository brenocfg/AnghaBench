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
typedef  int offsetT ;
struct TYPE_4__ {int fr_address; int fr_fix; int /*<<< orphan*/  fr_symbol; } ;
typedef  TYPE_1__ fragS ;
typedef  int /*<<< orphan*/  asection ;
typedef  int addressT ;

/* Variables and functions */
 int /*<<< orphan*/ * S_GET_SEGMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IS_DEFINED (int /*<<< orphan*/ ) ; 
 int relaxed_symbol_addr (TYPE_1__*,long) ; 

__attribute__((used)) static int
relax_adr (fragS *fragp, asection *sec, long stretch)
{
  addressT addr;
  offsetT val;

  /* Assume worst case for symbols not known to be in the same section.  */
  if (!S_IS_DEFINED(fragp->fr_symbol)
      || sec != S_GET_SEGMENT (fragp->fr_symbol))
    return 4;

  val = relaxed_symbol_addr(fragp, stretch);
  addr = fragp->fr_address + fragp->fr_fix;
  addr = (addr + 4) & ~3;
  /* Force misaligned targets to 32-bit variant.  */
  if (val & 3)
    return 4;
  val -= addr;
  if (val < 0 || val > 1020)
    return 4;
  return 2;
}