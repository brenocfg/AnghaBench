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
struct rtx_iv {scalar_t__ extend; int /*<<< orphan*/  extend_mode; void* mult; void* delta; void* step; void* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEG ; 
 scalar_t__ UNKNOWN ; 
 void* simplify_gen_unary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
iv_neg (struct rtx_iv *iv)
{
  if (iv->extend == UNKNOWN)
    {
      iv->base = simplify_gen_unary (NEG, iv->extend_mode,
				     iv->base, iv->extend_mode);
      iv->step = simplify_gen_unary (NEG, iv->extend_mode,
				     iv->step, iv->extend_mode);
    }
  else
    {
      iv->delta = simplify_gen_unary (NEG, iv->extend_mode,
				      iv->delta, iv->extend_mode);
      iv->mult = simplify_gen_unary (NEG, iv->extend_mode,
				     iv->mult, iv->extend_mode);
    }

  return true;
}