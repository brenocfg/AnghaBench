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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  MEM_P (scalar_t__) ; 
 scalar_t__ PLUS ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ stack_pointer_rtx ; 

__attribute__((used)) static int
stack_memref_p (rtx x)
{
  if (!MEM_P (x))
    return 0;
  x = XEXP (x, 0);

  if (x == stack_pointer_rtx)
    return 1;
  if (GET_CODE (x) == PLUS
      && XEXP (x, 0) == stack_pointer_rtx
      && GET_CODE (XEXP (x, 1)) == CONST_INT)
    return 1;

  return 0;
}