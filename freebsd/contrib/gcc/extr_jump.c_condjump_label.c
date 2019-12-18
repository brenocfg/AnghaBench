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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ IF_THEN_ELSE ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ pc_rtx ; 
 scalar_t__ pc_set (scalar_t__) ; 

rtx
condjump_label (rtx insn)
{
  rtx x = pc_set (insn);

  if (!x)
    return NULL_RTX;
  x = SET_SRC (x);
  if (GET_CODE (x) == LABEL_REF)
    return x;
  if (GET_CODE (x) != IF_THEN_ELSE)
    return NULL_RTX;
  if (XEXP (x, 2) == pc_rtx && GET_CODE (XEXP (x, 1)) == LABEL_REF)
    return XEXP (x, 1);
  if (XEXP (x, 1) == pc_rtx && GET_CODE (XEXP (x, 2)) == LABEL_REF)
    return XEXP (x, 2);
  return NULL_RTX;
}