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
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ offsettable_address_p (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rs6000_legitimate_offset_address_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool
rs6000_offsettable_memref_p (rtx op)
{
  if (!MEM_P (op))
    return false;

  /* First mimic offsettable_memref_p.  */
  if (offsettable_address_p (1, GET_MODE (op), XEXP (op, 0)))
    return true;

  /* offsettable_address_p invokes rs6000_mode_dependent_address, but
     the latter predicate knows nothing about the mode of the memory
     reference and, therefore, assumes that it is the largest supported
     mode (TFmode).  As a consequence, legitimate offsettable memory
     references are rejected.  rs6000_legitimate_offset_address_p contains
     the correct logic for the PLUS case of rs6000_mode_dependent_address.  */
  return rs6000_legitimate_offset_address_p (GET_MODE (op), XEXP (op, 0), 1);
}