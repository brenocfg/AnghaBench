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
 scalar_t__ CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pool_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_delegitimize_address (int /*<<< orphan*/ ) ; 

rtx
maybe_get_pool_constant (rtx x)
{
  x = ix86_delegitimize_address (XEXP (x, 0));

  if (GET_CODE (x) == SYMBOL_REF && CONSTANT_POOL_ADDRESS_P (x))
    return get_pool_constant (x);

  return NULL_RTX;
}