#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 scalar_t__ HAVE_32BIT_ADDRESSES ; 
 scalar_t__ HAVE_32BIT_SYMBOLS ; 
 scalar_t__ IS_ZEXT_32BIT_NUM (int) ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_symbol ; 

__attribute__((used)) static void
normalize_address_expr (expressionS *ex)
{
  if (((ex->X_op == O_constant && HAVE_32BIT_ADDRESSES)
	|| (ex->X_op == O_symbol && HAVE_32BIT_SYMBOLS))
      && IS_ZEXT_32BIT_NUM (ex->X_add_number))
    ex->X_add_number = (((ex->X_add_number & 0xffffffff) ^ 0x80000000)
			- 0x80000000);
}