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
struct ix86_address {scalar_t__ base; scalar_t__ index; scalar_t__ disp; scalar_t__ seg; int scale; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ SEG_DEFAULT ; 
 scalar_t__ SUBREG ; 
 void* SUBREG_REG (scalar_t__) ; 
 scalar_t__ TARGET_K6 ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int ix86_decompose_address (int /*<<< orphan*/ ,struct ix86_address*) ; 

__attribute__((used)) static int
ix86_address_cost (rtx x)
{
  struct ix86_address parts;
  int cost = 1;
  int ok = ix86_decompose_address (x, &parts);

  gcc_assert (ok);

  if (parts.base && GET_CODE (parts.base) == SUBREG)
    parts.base = SUBREG_REG (parts.base);
  if (parts.index && GET_CODE (parts.index) == SUBREG)
    parts.index = SUBREG_REG (parts.index);

  /* More complex memory references are better.  */
  if (parts.disp && parts.disp != const0_rtx)
    cost--;
  if (parts.seg != SEG_DEFAULT)
    cost--;

  /* Attempt to minimize number of registers in the address.  */
  if ((parts.base
       && (!REG_P (parts.base) || REGNO (parts.base) >= FIRST_PSEUDO_REGISTER))
      || (parts.index
	  && (!REG_P (parts.index)
	      || REGNO (parts.index) >= FIRST_PSEUDO_REGISTER)))
    cost++;

  if (parts.base
      && (!REG_P (parts.base) || REGNO (parts.base) >= FIRST_PSEUDO_REGISTER)
      && parts.index
      && (!REG_P (parts.index) || REGNO (parts.index) >= FIRST_PSEUDO_REGISTER)
      && parts.base != parts.index)
    cost++;

  /* AMD-K6 don't like addresses with ModR/M set to 00_xxx_100b,
     since it's predecode logic can't detect the length of instructions
     and it degenerates to vector decoded.  Increase cost of such
     addresses here.  The penalty is minimally 2 cycles.  It may be worthwhile
     to split such addresses or even refuse such addresses at all.

     Following addressing modes are affected:
      [base+scale*index]
      [scale*index+disp]
      [base+index]

     The first and last case  may be avoidable by explicitly coding the zero in
     memory address, but I don't have AMD-K6 machine handy to check this
     theory.  */

  if (TARGET_K6
      && ((!parts.disp && parts.base && parts.index && parts.scale != 1)
	  || (parts.disp && !parts.base && parts.index && parts.scale != 1)
	  || (!parts.disp && parts.base && parts.index && parts.scale == 1)))
    cost += 10;

  return cost;
}