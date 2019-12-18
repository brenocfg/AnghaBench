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
struct rtx_iv {int mode; int first_special; int extend_mode; int /*<<< orphan*/  mult; void* delta; int /*<<< orphan*/  extend; void* step; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNKNOWN ; 
 int VOIDmode ; 
 void* const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 

__attribute__((used)) static bool
iv_constant (struct rtx_iv *iv, rtx cst, enum machine_mode mode)
{
  if (mode == VOIDmode)
    mode = GET_MODE (cst);

  iv->mode = mode;
  iv->base = cst;
  iv->step = const0_rtx;
  iv->first_special = false;
  iv->extend = UNKNOWN;
  iv->extend_mode = iv->mode;
  iv->delta = const0_rtx;
  iv->mult = const1_rtx;

  return true;
}