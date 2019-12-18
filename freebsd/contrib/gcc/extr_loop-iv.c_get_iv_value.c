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
struct rtx_iv {scalar_t__ step; scalar_t__ base; scalar_t__ extend; scalar_t__ delta; scalar_t__ mult; int /*<<< orphan*/  extend_mode; int /*<<< orphan*/  mode; int /*<<< orphan*/  first_special; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  MULT ; 
 int /*<<< orphan*/  PLUS ; 
 scalar_t__ UNKNOWN ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ lowpart_subreg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ simplify_gen_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ simplify_gen_unary (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

rtx
get_iv_value (struct rtx_iv *iv, rtx iteration)
{
  rtx val;

  /* We would need to generate some if_then_else patterns, and so far
     it is not needed anywhere.  */
  gcc_assert (!iv->first_special);

  if (iv->step != const0_rtx && iteration != const0_rtx)
    val = simplify_gen_binary (PLUS, iv->extend_mode, iv->base,
			       simplify_gen_binary (MULT, iv->extend_mode,
						    iv->step, iteration));
  else
    val = iv->base;

  if (iv->extend_mode == iv->mode)
    return val;

  val = lowpart_subreg (iv->mode, val, iv->extend_mode);

  if (iv->extend == UNKNOWN)
    return val;

  val = simplify_gen_unary (iv->extend, iv->extend_mode, val, iv->mode);
  val = simplify_gen_binary (PLUS, iv->extend_mode, iv->delta,
			     simplify_gen_binary (MULT, iv->extend_mode,
						  iv->mult, val));

  return val;
}