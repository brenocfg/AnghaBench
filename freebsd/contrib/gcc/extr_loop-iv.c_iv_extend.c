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
struct rtx_iv {scalar_t__ step; int extend_mode; scalar_t__ extend; int mode; int /*<<< orphan*/  mult; scalar_t__ delta; int /*<<< orphan*/  base; int /*<<< orphan*/  first_special; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ UNKNOWN ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  get_iv_value (struct rtx_iv*,scalar_t__) ; 
 int /*<<< orphan*/  simplify_gen_unary (int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
iv_extend (struct rtx_iv *iv, enum rtx_code extend, enum machine_mode mode)
{
  /* If iv is invariant, just calculate the new value.  */
  if (iv->step == const0_rtx
      && !iv->first_special)
    {
      rtx val = get_iv_value (iv, const0_rtx);
      val = simplify_gen_unary (extend, mode, val, iv->extend_mode);

      iv->base = val;
      iv->extend = UNKNOWN;
      iv->mode = iv->extend_mode = mode;
      iv->delta = const0_rtx;
      iv->mult = const1_rtx;
      return true;
    }

  if (mode != iv->extend_mode)
    return false;

  if (iv->extend != UNKNOWN
      && iv->extend != extend)
    return false;

  iv->extend = extend;

  return true;
}