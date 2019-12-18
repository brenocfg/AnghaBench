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
 scalar_t__ CONSTANT_POOL_ADDRESS_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pool_constant (scalar_t__) ; 
 int rtx_equal_p (scalar_t__,scalar_t__) ; 
 int rtx_referenced_p (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtx_referenced_p_1 (rtx *body, void *x)
{
  rtx y = (rtx) x;

  if (*body == NULL_RTX)
    return y == NULL_RTX;

  /* Return true if a label_ref *BODY refers to label Y.  */
  if (GET_CODE (*body) == LABEL_REF && LABEL_P (y))
    return XEXP (*body, 0) == y;

  /* If *BODY is a reference to pool constant traverse the constant.  */
  if (GET_CODE (*body) == SYMBOL_REF
      && CONSTANT_POOL_ADDRESS_P (*body))
    return rtx_referenced_p (y, get_pool_constant (*body));

  /* By default, compare the RTL expressions.  */
  return rtx_equal_p (*body, y);
}