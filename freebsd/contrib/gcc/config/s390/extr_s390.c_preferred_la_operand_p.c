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
struct s390_address {scalar_t__ indx; scalar_t__ base; scalar_t__ pointer; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REGNO_OK_FOR_BASE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO_OK_FOR_INDEX_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ REG_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  s390_decompose_address (scalar_t__,struct s390_address*) ; 

bool
preferred_la_operand_p (rtx op1, rtx op2)
{
  struct s390_address addr;

  if (op2 != const0_rtx)
    op1 = gen_rtx_PLUS (Pmode, op1, op2);

  if (!s390_decompose_address (op1, &addr))
    return false;
  if (addr.base && !REGNO_OK_FOR_BASE_P (REGNO (addr.base)))
    return false;
  if (addr.indx && !REGNO_OK_FOR_INDEX_P (REGNO (addr.indx)))
    return false;

  if (!TARGET_64BIT && !addr.pointer)
    return false;

  if (addr.pointer)
    return true;

  if ((addr.base && REG_P (addr.base) && REG_POINTER (addr.base))
      || (addr.indx && REG_P (addr.indx) && REG_POINTER (addr.indx)))
    return true;

  return false;
}